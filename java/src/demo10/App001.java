/*
 * THREAD POOL
 * Version "preparation"
 *
 * To get started with thread pool, first, introducing "future".
*/

package demo10;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class App001 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newSingleThreadExecutor();

        Future<String> task = executor.submit(() -> "foo");

        executor.shutdown();

        while (false == task.isDone()) {
            // Waiting...
            // Thread.sleep(500);
        }

        String result = task.get();
        System.out.println(result);
    }

}
