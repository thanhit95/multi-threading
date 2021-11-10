/*
 * THREAD POOL
 * Version C04: Thread pool and Future - Getting started
*/

package demo10;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppC04 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newSingleThreadExecutor();

        // Old syntax
//        Callable<Integer> caGetSquared = new Callable<>() {
//            @Override
//            public Integer call() throws Exception {
//                return getSquared(7);
//            }
//        };

        Callable<Integer> callable = () -> getSquared(7);
        Future<Integer> task = executor.submit(callable);

        executor.shutdown();

        System.out.println("Calculating...");

        Integer result = task.get();
        System.out.println(result);
    }


    private static int getSquared(int x) {
        // Calculating in three seconds...
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return x * x;
    }

}
