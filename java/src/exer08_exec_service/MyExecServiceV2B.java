/*
 * MY EXECUTOR SERVICE
 *
 * Version 2B: The executor service storing running tasks
 * - Method "waitTaskDone" uses a condition variable to synchronize.
 */

package exer08_exec_service;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.stream.IntStream;



public final class MyExecServiceV2B {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();

    private final Queue<Runnable> taskPending = new LinkedList<>();
    private final Queue<Runnable> taskRunning = new LinkedList<>();

    private volatile boolean forceThreadShutdown = false;



    public MyExecServiceV2B(int numThreads) {
        init(numThreads);
    }



    private void init(int inpNumThreads) {
//      shutdown();

        numThreads = inpNumThreads;
        forceThreadShutdown = false;

        lstTh = IntStream.range(0, numThreads)
                .mapToObj(i -> new Thread(() -> threadWorkerFunc(this)))
                .toList();

        lstTh.forEach(Thread::start);
    }



    public void submit(Runnable task) {
        synchronized (taskPending) {
            taskPending.add(task);
            taskPending.notify();
        }
    }



//    public void waitTaskDoneBad() {
//        try {
//            for (;;) {
//                synchronized (taskRunning) {
//                    while (!taskRunning.isEmpty())
//                        taskRunning.wait();
//
//                    synchronized (taskPending) {
//                        if (taskPending.isEmpty())
//                            break;
//                    }
//                }
//            }
//        }
//        catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//    }



    public void waitTaskDone() {
        try {
            for (;;) {
                synchronized (taskPending) {
                    if (taskPending.isEmpty()) {
                        synchronized (taskRunning) {
                            while (!taskRunning.isEmpty())
                                taskRunning.wait();

                            // no pending task and no running task
                            break;
                        }
                    }
                }
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    public void shutdown() {
        synchronized (taskPending) {
            forceThreadShutdown = true;
            taskPending.clear();
            taskPending.notifyAll();
        }

        for (var th : lstTh) {
            try {
                th.join();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        numThreads = 0;
//      lstTh.clear();
        taskRunning.clear();
    }



    private static void threadWorkerFunc(MyExecServiceV2B thisPtr) {
        var taskPending = thisPtr.taskPending;
        var taskRunning = thisPtr.taskRunning;
        Runnable task;

        try {
            for (;;) {
                synchronized (taskPending) {
                    // WAIT FOR AN AVAILABLE PENDING TASK
                    while (taskPending.isEmpty() && false == thisPtr.forceThreadShutdown) {
                        taskPending.wait();
                    }

                    if (thisPtr.forceThreadShutdown) {
                        break;
                    }

                    // GET THE TASK FROM THE PENDING QUEUE
                    task = taskPending.remove();

                    // PUSH IT TO THE RUNNING QUEUE
                    synchronized (taskRunning) {
                        taskRunning.add(task);
                    }
                }

                // DO THE TASK
                task.run();

                // REMOVE IT FROM THE RUNNING QUEUE
                synchronized (taskRunning) {
                    taskRunning.remove(task);
                    taskRunning.notify();
                }
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
