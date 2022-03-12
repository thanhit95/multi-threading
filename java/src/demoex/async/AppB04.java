/*
 * ASYNCHRONOUS PROGRAMMING WITH THE FUTURE/TASK
 */

package demoex.async;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppB04 {

    private static ExecutorService executor = Executors.newFixedThreadPool(5);


    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Future<Boolean> taskValidation = executor.submit(() -> validate("John"));

        boolean result = taskValidation.get();

        if (result)
            System.out.println("User can view movies.");
        else
            System.out.println("Age must be >= 18 to view movies.");

        executor.shutdown();
    }


    private static boolean validate(String userName) throws InterruptedException, ExecutionException {
        var taskGettingAge = executor.submit(() -> queryUserAge(userName));
        int userAge = taskGettingAge.get();

        System.out.println("Validating...");

        // Validating in two seconds...
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return userAge >= 18;
    }


    private static int queryUserAge(String userName) {
        System.out.println("Querying userAge in database...");

        // Querying database in two seconds...
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        if (userName.equals("Thanh"))
            return 26;
        else
            return 17;
    }

}
