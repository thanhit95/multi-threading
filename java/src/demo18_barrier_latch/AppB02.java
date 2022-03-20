/*
 * BARRIERS AND LATCHES
 * Version B: Count-down latches
 *
 * Main thread waits for 3 child threads to get enough data to progress.
 */

package demo18_barrier_latch;

import java.util.List;
import java.util.concurrent.CountDownLatch;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException {
        var lstArg = List.of(
                new ThreadArg("Send request to egg.net to get data", 6),
                new ThreadArg("Send request to foo.org to get data", 2),
                new ThreadArg("Send request to bar.com to get data", 4)
        );


        var syncPoint = new CountDownLatch(lstArg.size());


        lstArg.forEach(arg -> new Thread(() -> {
            try {
                Thread.sleep(1000 * arg.timeWait);

                System.out.println(arg.message);
                syncPoint.countDown();

                Thread.sleep(8000);
                System.out.println("Cleanup");
            }
            catch (InterruptedException e) {
            }
        }).start());


        syncPoint.await();

        System.out.println("\nNow we have enough data to progress to next step\n");
    }



    private record ThreadArg(String message, int timeWait) { }

}
