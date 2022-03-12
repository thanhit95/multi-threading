/*
 * MY EXECUTOR SERVICE
 *
 * Version 2A: The executor service storing running tasks
 * - Method "waitTaskDone" uses a semaphore to synchronize.
 */

package exer07;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.stream.IntStream;



public class MyExecServiceV2A {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();

    private Queue<Runnable> taskPending = new LinkedList<>();
    private Queue<Runnable> taskRunning = new LinkedList<>();

    private Semaphore counterTaskRunning = new Semaphore(0);

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



    public void waitTaskDone() {
        for (;;) {
            try {
                counterTaskRunning.acquire();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

            synchronized (taskPending) {
                synchronized (taskRunning) {
                    if (0 == taskPending.size() && 0 == taskRunning.size()
                                                /* && 0 == counterTaskRunning.availablePermits() */
                    )
                        break;
                }
            }
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
//          lstTh.clear();
            taskRunning.clear();

            counterTaskRunning.release(counterTaskRunning.availablePermits());
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    private static void threadWorkerFunc(MyExecServiceV2A thisPtr) {
        var taskPending = thisPtr.taskPending;
        var taskRunning = thisPtr.taskRunning;
        var counterTaskRunning = thisPtr.counterTaskRunning;

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
                }

                counterTaskRunning.release();
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
