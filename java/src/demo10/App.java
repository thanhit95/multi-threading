/*
 * THREAD YIELDING
 */

package demo10;

import java.time.Duration;
import java.time.Instant;



public class App {

    public static void main(String[] args) {
        var tpStart = Instant.now();

        littleSleep(130000);

        var timeElapsed = Duration.between(tpStart, Instant.now());

        System.out.println("Elapsed time: " + timeElapsed.toNanos() + " nanoseonds");
    }


    private static void littleSleep(int ns) {
        var tpStart = Instant.now();
        var tpEnd = tpStart.plusNanos(ns);

        do {
            Thread.yield();
        }
        while (Instant.now().isBefore(tpEnd));
    }

}
