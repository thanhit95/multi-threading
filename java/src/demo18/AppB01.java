/*
 * BARRIERS
 * Version B: Count-down latches
 */

package demo18;

import java.util.List;
import java.util.concurrent.CountDownLatch;



public class AppB01 {

    public static void main(String[] args) {
        var syncPoint = new CountDownLatch(3); // participant count = 3


        var lstArgs = List.of(
                new ThreadArg("foo", 1),
                new ThreadArg("bar", 2),
                new ThreadArg("ham", 3)
        );


        lstArgs.forEach(arg -> new Thread(() -> {

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

        }).start());
    }



    record ThreadArg(String userName, int timeWait) { }

}
