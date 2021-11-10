/*
 * THREAD POOL
 * Version C03: Thread pool and Future - Getting started
*/

package demo10;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppC03 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newSingleThreadExecutor();

        Future<Integer> task = executor.submit(() -> getSquared(7));
        executor.shutdown();

        /*
         * Method "Future.get" should wait if necessary for the computation to complete,
         * and then retrieves its result.
         *
         * So, we can omit the while loop (to wait for task completion).
         */

        Integer result = task.get();
        System.out.println(result);
    }


    private static int getSquared(int x) {
        return x * x;
    }

}
