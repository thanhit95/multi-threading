/*
 * MY EXECUTOR SERVICE
 *
 * Version 0B: The easiest executor service
 * - It uses a blocking queue as underlying mechanism.
 * - It supports waitTaskDone() and shutdown().
 */

package exer07_exec_service;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;



public final class MyExecServiceV0B {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();

    private final BlockingQueue<Runnable> taskPending = new LinkedBlockingQueue<>();
    private final AtomicInteger counterTaskRunning = new AtomicInteger();

    private volatile boolean forceThreadShutdown = false;

    private static final Runnable emptyTask = () -> { };



    public MyExecServiceV0B(int numThreads) {
        init(numThreads);
    }



    private void init(int inpNumThreads) {
        numThreads = inpNumThreads;
        counterTaskRunning.set(0);
        forceThreadShutdown = false;

        lstTh = IntStream.range(0, numThreads)
                .mapToObj(i -> new Thread(() -> threadWorkerFunc(this)))
                .toList();

        lstTh.forEach(Thread::start);
    }



    public void submit(Runnable task) {
        taskPending.add(task);
    }



    public void waitTaskDone() {
        // This ExecService is too simple,
        // so there is no good implementation for waitTaskDone()
        try {
            while (!taskPending.isEmpty() || counterTaskRunning.get() > 0) {
                Thread.sleep(1000);
                // Thread.yield();
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    public void shutdown() {
        forceThreadShutdown = true;
        taskPending.clear();

        // Invoke blocked threads by adding "empty" tasks
        for (int i = 0; i < numThreads; ++i) {
            taskPending.add(emptyTask);
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



    private static void threadWorkerFunc(MyExecServiceV0B thisPtr) {
        Runnable task;

        try {
            for (;;) {
                // WAIT FOR AN AVAILABLE PENDING TASK
                task = thisPtr.taskPending.take();

                // If shutdown() was called, then exit the function
                if (thisPtr.forceThreadShutdown) {
                    break;
                }

                // DO THE TASK
                thisPtr.counterTaskRunning.incrementAndGet();
                task.run();
                thisPtr.counterTaskRunning.decrementAndGet();
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
