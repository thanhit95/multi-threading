/*
 * MY EXECUTOR SERVICE
 *
 * Version 0A: The easiest executor service
 * - It uses a blocking queue as underlying mechanism.
 */

package exer07;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.IntStream;



public final class MyExecServiceV0A {

    private int numThreads = 0;
    private List<Thread> lstTh = new LinkedList<>();
    private BlockingQueue<Runnable> taskPending = new LinkedBlockingQueue<>();



    public MyExecServiceV0A(int numThreads) {
        init(numThreads);
    }



    private void init(int inpNumThreads) {
        numThreads = inpNumThreads;

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
        // so there is no implementation for waitTaskDone()
        try {
            Thread.sleep(11000); // fake behaviour
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    public void shutdown() {
        // This ExecService is too simple,
        // so there is no implementation for shutdown()
        System.out.println("No implementation for shutdown().");
        System.out.println("You need to exit the app manually.");
    }



    private static void threadWorkerFunc(MyExecServiceV0A thisPtr) {
        Runnable task = null;

        try {
            for (;;) {
                // WAIT FOR AN AVAILABLE PENDING TASK
                task = thisPtr.taskPending.take();

                // DO THE TASK
                task.run();
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
