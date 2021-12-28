/*
 * THREAD POOLS
 * Version C05: Thread pools and Future objects - List of Future objects
 */

package demo11;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;



public class AppC05 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        final int NUM_THREADS = 2;
        final int NUM_TASKS = 5;

        ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);

        System.out.println("Begin to submit all tasks");

        // lstTask is List< Future<Character> >
        var lstTask = IntStream.range(0, NUM_TASKS)
                .mapToObj(i -> executor.submit(() -> (char)(i + 'A')))
                .toList();

        executor.shutdown();

        for (var task : lstTask) {
            System.out.println(task.get());
        }
    }

}
