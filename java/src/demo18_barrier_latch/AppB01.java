/*
 * BARRIERS AND LATCHES
 * Version B: Count-down latches
 *
 * Notes:
 * - CyclicBarrier maintains a count of threads whereas CountDownLatch maintains a count of tasks.
 * - CountDownLatch in Java is different from that one in C++.
 */

package demo18_barrier_latch;

import java.util.List;
import java.util.concurrent.CountDownLatch;



public class AppB01 {

    public static void main(String[] args) {
        var syncPoint = new CountDownLatch(3); // participant count = 3


        var lstArg = List.of(
                new ThreadArg("lorem", 1),
                new ThreadArg("ipsum", 2),
                new ThreadArg("dolor", 3)
        );


        lstArg.forEach(arg -> new Thread(() -> {

            try {
                Thread.sleep(1000 * arg.timeWait);

                System.out.println("Get request from " + arg.userName);

                syncPoint.countDown();
                syncPoint.await();

                System.out.println("Done " + arg.userName);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

        }).start());
    }



    private record ThreadArg(String userName, int timeWait) { }

}
