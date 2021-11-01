/*
 * FUTURE
*/

package demo10;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class App {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newSingleThreadExecutor();

        Future<String> fut = executor.submit(() -> "foo");

        while (fut.isDone() == false) {
            Thread.sleep(500);
        }

        executor.shutdown();

        String result = fut.get();
        System.out.println(result);
    }

}
