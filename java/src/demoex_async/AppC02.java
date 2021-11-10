/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
*/

package demoex_async;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;



public class AppC02 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        CompletableFuture<Void> task;

        task = CompletableFuture
                .supplyAsync(() -> getSquared(7))
                .thenApply(AppC02::getDiv2)
                .thenAccept(System.out::println);

        task.get();
    }


    private static int getSquared(int x) {
        return x * x;
    }


    private static int getDiv2(int x) {
        return x / 2;
    }

}
