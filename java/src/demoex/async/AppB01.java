/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 *
 * The app takes about 1000 miliseconds to run
 * because all 3 tasks are running simultaneously.
*/

package demoex.async;

import java.time.Duration;
import java.time.Instant;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class AppB01 {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        // A pool of 5 threads, which helps us to do asynchronous tasks
        ExecutorService executor = Executors.newFixedThreadPool(5);

        var timePointStart = Instant.now();

        Future<Void> taskA = executor.submit(() -> doAction("cooking eggs"));
        Future<Void> taskB = executor.submit(() -> doAction("making coffee"));
        Future<Void> taskC = executor.submit(() -> doAction("watching movies"));

        taskA.get();
        taskB.get();
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
