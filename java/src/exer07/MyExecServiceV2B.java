/*
 * MY EXECUTOR SERVICE
 *
 * Version 2B:
 *   - Better synchronization.
 *   - Method "waitTaskDone":
 *       + uses a condition variable to synchronize.
 *       + does not consume CPU (compared to version 1).
 */

package exer07;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.stream.IntStream;



public class MyExecServiceV2B {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();

    private Queue<Runnable> taskPending = new LinkedList<>();
    private Queue<Runnable> taskRunning = new LinkedList<>();

    private volatile boolean forceThreadShutdown = false;



    public void init(int inpNumThreads) {
        shutdown();

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
//                    while (taskRunning.size() > 0)
//                        taskRunning.wait();
//
//                    synchronized (taskPending) {
//                        if (0 == taskPending.size())
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
                    if (0 == taskPending.size()) {
                        synchronized (taskRunning) {
                            while (taskRunning.size() > 0)
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
        try {
            synchronized (taskPending) {
                forceThreadShutdown = true;
                taskPending.clear();
                taskPending.notifyAll();
            }

            for (var th : lstTh)
                th.join();

            numThreads = 0;
            lstTh.clear();
            taskRunning.clear();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    private static void threadWorkerFunc(MyExecServiceV2B thisPtr) {
        var taskPending = thisPtr.taskPending;
        var taskRunning = thisPtr.taskRunning;
        Runnable task = null;

        try {
            for (;;) {
                synchronized (taskPending) {
                    // WAIT FOR AN AVAILABLE PENDING TASK
                    while (0 == taskPending.size() && false == thisPtr.forceThreadShutdown) {
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
