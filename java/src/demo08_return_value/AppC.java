/*
 * GETTING RETURNED VALUES FROM THREADS
 */

package demo08_return_value;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppC {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        var cal = new SimpleCalculator();
        System.out.println("Begin calculating");

        var futResult = cal.calculate(-9);

        var result = futResult.get();

        System.out.println(result);

        cal.shutdown();
    }

}



class SimpleCalculator {
    private ExecutorService executor = Executors.newSingleThreadExecutor();

    public Future<Integer> calculate(Integer input) {
        return executor.submit(() -> {
            Thread.sleep(1000);
            return input * 2;
        });
    }

    public void shutdown() {
        executor.shutdown();
    }
}
