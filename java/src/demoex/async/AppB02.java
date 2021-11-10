/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 *
 * The app takes about 3000 miliseconds to run
 * because each method "Future.get" pauses app until the task finishes.
*/

package demoex.async;

import java.time.Duration;
import java.time.Instant;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newFixedThreadPool(5);

        var timePointStart = Instant.now();

        Future<Void> taskA = executor.submit(() -> doAction("cooking eggs"));
        taskA.get();

        Future<Void> taskB = executor.submit(() -> doAction("making coffee"));
        taskB.get();

        Future<Void> taskC = executor.submit(() -> doAction("watching movies"));
        taskC.get();

        var timePointEnd = Instant.now();
        var duration = Duration.between(timePointStart, timePointEnd).toMillis();

        executor.shutdown();

        System.out.println("Total time: " + duration + " millis");
    }


    private static Void doAction(String actionName) {
        System.out.println(actionName);

        // Doing action in one second...
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return null;
    }

}
