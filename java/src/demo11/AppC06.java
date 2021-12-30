/*
 * THREAD POOLS
 * Version C06: Thread pools and Future objects - List of Future objects
 */

package demo11;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;



public class AppC06 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        final int NUM_THREADS = 2;
        final int NUM_TASKS = 5;

        ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);

        // List< Callable<String> > todo
        var todo = IntStream.range(0, NUM_TASKS)
                .mapToObj(i -> (Callable<String>)() -> doTask(i))
                .toList();

        System.out.println("Begin to submit all tasks");

        /*
         * invokeAll() will not return until all the tasks are completed
         * (i.e., all the Futures in your answer collection will report isDone() if asked)
         */

        // lstTask is List< Future<String> >
        var lstTask = executor.invokeAll(todo);

        System.out.println("All tasks are completed");
        executor.shutdown();

        for (var task : lstTask) {
            System.out.println(task.get());
        }
    }



    private static String doTask(int number) {
        try { Thread.sleep(1000); } catch (InterruptedException e) { }
        System.out.println("Finish " + number);
        return number + " ok";
    }

}
