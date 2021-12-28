/*
 * BARRIERS
 * Version A: Cyclic barriers
 */

package demo18;

import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;



public class AppA01 {

    public static void main(String[] args) {
        var syncPoint = new CyclicBarrier(3); // participant count = 3


        var lstArgs = List.of(
                new ThreadArg("foo", 1),
                new ThreadArg("bar", 2),
                new ThreadArg("ham", 3)
        );


        lstArgs.forEach(arg -> new Thread(() -> {

            try {
                Thread.sleep(1000 * arg.timeWait());

                System.out.println("Get request from " + arg.userName());

                syncPoint.await();

                System.out.println("Process request for " + arg.userName());

                syncPoint.await();

                System.out.println("Done " + arg.userName());
            }
            catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

        }).start());
    }



    record ThreadArg(String userName, int timeWait) { }

}
