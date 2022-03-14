/*
 * MY EXECUTOR SERVICE
 *
 * Version 1A: Simple executor service
 * - Method "waitTaskDone" consumes CPU (due to bad synchronization).
 */

package exer07;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;



public final class MyExecServiceV1A {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();

    private Queue<Runnable> taskPending = new LinkedList<>();
    private AtomicInteger counterTaskRunning = new AtomicInteger();

    private volatile boolean forceThreadShutdown = false;



    public MyExecServiceV1A(int numThreads) {
        init(numThreads);
    }



    private void init(int inpNumThreads) {
//      shutdown();

        numThreads = inpNumThreads;
        counterTaskRunning.set(0);
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
        boolean done = false;

        for (;;) {
            synchronized (taskPending) {
                if (0 == taskPending.size() && 0 == counterTaskRunning.get()) {
                    done = true;
                }
            }

            if (done)
                break;

            Thread.yield();
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
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    private static void threadWorkerFunc(MyExecServiceV1A thisPtr) {
        var taskPending = thisPtr.taskPending;
        var counterTaskRunning = thisPtr.counterTaskRunning;

        Runnable task = null;

        try {
            for (;;) {
                // WAIT FOR AN AVAILABLE PENDING TASK
                synchronized (taskPending) {
                    while (0 == taskPending.size() && false == thisPtr.forceThreadShutdown) {
                        taskPending.wait();
                    }

                    if (thisPtr.forceThreadShutdown) {
                        break;
                    }

                    // GET THE TASK FROM THE PENDING QUEUE
                    task = taskPending.remove();

                    counterTaskRunning.getAndIncrement();
                }

                // DO THE TASK
                task.run();
                counterTaskRunning.getAndDecrement();
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
