/*
 * MY EXECUTOR SERVICE
 *
 * Version 1B: Simple executor service
 * - Method "waitTaskDone" uses a condition variable to synchronize.
 */

package exer07_exec_service;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.stream.IntStream;



public final class MyExecServiceV1B {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();

    private final Queue<Runnable> taskPending = new LinkedList<>();

    private int counterTaskRunning;
    private final Object lkTaskRunning = new Object();

    private volatile boolean forceThreadShutdown = false;



    public MyExecServiceV1B(int numThreads) {
        init(numThreads);
    }



    private void init(int inpNumThreads) {
//      shutdown();

        numThreads = inpNumThreads;
        counterTaskRunning = 0;
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



    public void waitTaskDone() {
        for (;;) {
            synchronized (taskPending) {
                if (taskPending.isEmpty()) {
                    synchronized (lkTaskRunning) {
                        try {
                            while (counterTaskRunning > 0) {
                                lkTaskRunning.wait();
                            }

                            // no pending task and no running task
                            break;
                        }
                        catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
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
    }



    private static void threadWorkerFunc(MyExecServiceV1B thisPtr) {
        var taskPending = thisPtr.taskPending;
        var lkTaskRunning = thisPtr.lkTaskRunning;

        Runnable task;

        try {
            for (;;) {
                // WAIT FOR AN AVAILABLE PENDING TASK
                synchronized (taskPending) {
                    while (taskPending.isEmpty() && false == thisPtr.forceThreadShutdown) {
                        taskPending.wait();
                    }

                    if (thisPtr.forceThreadShutdown) {
                        break;
                    }

                    // GET THE TASK FROM THE PENDING QUEUE
                    task = taskPending.remove();

                    ++thisPtr.counterTaskRunning;
                }

                // DO THE TASK
                task.run();

                synchronized (lkTaskRunning) {
                    --thisPtr.counterTaskRunning;

                    if (0 == thisPtr.counterTaskRunning) {
                        lkTaskRunning.notify();
                    }
                }
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
