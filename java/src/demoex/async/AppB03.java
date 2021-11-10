/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
*/

package demoex.async;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppB03 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newFixedThreadPool(5);

        Future<String> taskCookingEggs = executor.submit(() -> cookEggs());
        Future<String> taskMakingCoffee = executor.submit(() -> makeCoffee());

        executor.shutdown();

        String resultEggs = taskCookingEggs.get();
        String resultCoffee = taskMakingCoffee.get();

        System.out.println("Done!");
        System.out.println(resultEggs);
        System.out.println(resultCoffee);
    }


    private static String cookEggs() {
        System.out.println("I am cooking eggs");

        // Cooking eggs in two seconds...
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return "fried eggs";
    }


    private static String makeCoffee() {
        System.out.println("I am making coffee");

        // Making coffee in four seconds...
        try {
            Thread.sleep(4000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return "a cup of coffee";
    }

}
