/*
 * THREAD POOL
 * Version C01: Thread pool and Future
 *
 * Future object allows a way for you to programatically manage the task, such as:
 * - Wait for the task to finish executing (and get result), with get method.
 * - Cancel the task prematurely, with the cancel method.
*/

package demo10;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;



public class AppC01 {

    public static void main(String[] args) {
        final int NUM_THREADS = 2;
        final int NUM_TASKS = 5;


        ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);


        System.out.println("Begin to submit all tasks");


        var lstFuture = IntStream.range(0, NUM_TASKS)
                .mapToObj(i -> executor.submit(() -> (char)(i + 'A')))
                .toList();


        executor.shutdown();


        lstFuture.forEach(fut -> {
            try {
                System.out.println(fut.get());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        });
    }

}
