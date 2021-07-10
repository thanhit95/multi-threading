package ex06;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.stream.IntStream;



public class MyThreadPoolV2 {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();
    private Queue<Runnable> taskPending = new LinkedList<>();
    private Queue<Runnable> taskRunning = new LinkedList<>();
    private volatile boolean forceThreadShutdown = false;

    private Semaphore counterTaskRunning = new Semaphore(0);



    public void init(int inpNumThreads) {
        shutdown();

        numThreads = inpNumThreads;
        forceThreadShutdown = false;

        lstTh = IntStream.range(0, numThreads).mapToObj(i -> new Thread(() -> threadRoutine(this))).toList();

        lstTh.forEach(Thread::start);
    }



    void submit(Runnable task) {
        synchronized (taskPending) {
            taskPending.add(task);
            taskPending.notify();
        }
    }



    void waitTaskDone() {
        while (true) {
            try {
                counterTaskRunning.acquire();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

            synchronized (taskRunning) {
                synchronized (taskPending) {
                    if (taskPending.size() == 0 && taskRunning.size() == 0
                                                && counterTaskRunning.availablePermits() == 0)
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
            // lstTh.clear();

            taskRunning.clear();
            counterTaskRunning.release(counterTaskRunning.availablePermits());
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    private static void threadRoutine(MyThreadPoolV2 thisPtr) {
        var taskPending = thisPtr.taskPending;
        var taskRunning = thisPtr.taskRunning;
        var counterTaskRunning = thisPtr.counterTaskRunning;

        Runnable task = null;

        try {
            for (;;) {
                // WAITING FOR A PENDING TASK
                synchronized (taskPending) {
                    while (taskPending.size() == 0 && false == thisPtr.forceThreadShutdown) {
                        taskPending.wait();
                    }

                    if (thisPtr.forceThreadShutdown) {
                        break;
                    }

                    // GET THE TASK FROM THE PENDING QUEUE
                    task = taskPending.remove();
                    taskRunning.add(task);
                }

                // DO THE TASK
                task.run();

                synchronized (taskRunning) {
                    taskRunning.remove(task);
                    counterTaskRunning.release();
                }
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
