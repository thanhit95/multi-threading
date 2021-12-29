/*
 * BARRIERS
 * Version B: Count-down latches
 *
 * Notes:
 * - CyclicBarrier maintains a count of threads whereas CountDownLatch maintains a count of tasks.
 * - CountDownLatch in Java is different from that one in C++.
 */

package demo18;

import java.util.List;
import java.util.concurrent.CountDownLatch;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException {
        var syncPoint = new CountDownLatch(3); // participant count = 3


        var lstArgs = List.of(
                new ThreadArg("lorem", 1),
                new ThreadArg("ipsum", 2),
                new ThreadArg("dolor", 3)
        );


        for (int repeatCount = 0; repeatCount < 2; ++repeatCount) {
            var lstTh = lstArgs.stream().map(arg -> new Thread(() -> {

                try {
                    Thread.sleep(1000 * arg.timeWait());

                    System.out.println("Get request from " + arg.userName());

                    syncPoint.countDown();

                    syncPoint.await();

                    System.out.println("Done " + arg.userName());
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }

            })).toList();


            for (var th : lstTh)
                th.start();

            for (var th : lstTh)
                th.join();
        }
    }



    record ThreadArg(String userName, int timeWait) { }

}
