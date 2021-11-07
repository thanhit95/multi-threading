/*
 * THREAD POOL
 * Version "preparation"
 *
 * To get started with thread pool, first, introducing "future".
*/

package demo10;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class App004 {

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

        Integer result = task.get();
        System.out.println(result);
    }


    private static int getSquared(int x) {
        return x * x;
    }

}
