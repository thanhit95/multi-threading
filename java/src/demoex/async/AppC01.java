/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 *
 * From Javadoc: CompletableFuture is a Future that may be explicitly completed
 * (setting its value and status), and may be used as a CompletionStage,
 * supporting dependent functions and actions that trigger upon its completion.
 *
 * From that definition, CompletableFuture can be called as "Promise".
 */

package demoex.async;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;



public class AppC01 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        CompletableFuture<Integer> task;

        task = CompletableFuture
                .supplyAsync(() -> getSquared(7))
                .thenApply(AppC01::getDiv2);

        Integer result = task.get();
        System.out.println(result);
    }


    private static int getSquared(int x) {
        return x * x;
    }


    private static int getDiv2(int x) {
        return x / 2;
    }

}
