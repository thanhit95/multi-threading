/*
 * BARRIERS AND LATCHES
 * Version A: Cyclic barriers
 */

package demo18_barrier_latch;

import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;



public class AppA01 {

    public static void main(String[] args) {
        var syncPoint = new CyclicBarrier(3); // participant count = 3


        var lstArg = List.of(
                new ThreadArg("lorem", 1),
                new ThreadArg("ipsum", 2),
                new ThreadArg("dolor", 3)
        );


        lstArg.forEach(arg -> new Thread(() -> {

            try {
                Thread.sleep(1000 * arg.timeWait);

                System.out.println("Get request from " + arg.userName);
                syncPoint.await();

                System.out.println("Process request for " + arg.userName);
                syncPoint.await();

                System.out.println("Done " + arg.userName);
            }
            catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

        }).start());
    }



    private record ThreadArg(String userName, int timeWait) { }

}
