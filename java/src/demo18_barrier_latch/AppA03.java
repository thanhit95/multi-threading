/*
 * BARRIERS AND LATCHES
 * Version A: Cyclic barriers
 */

package demo18_barrier_latch;

import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;



public class AppA03 {

    public static void main(String[] args) {
        var syncPointA = new CyclicBarrier(2);
        var syncPointB = new CyclicBarrier(2);


        var lstArg = List.of(
                new ThreadArg("lorem", 1),
                new ThreadArg("ipsum", 3),
                new ThreadArg("dolor", 3),
                new ThreadArg("amet", 10)
        );


        lstArg.forEach(arg -> new Thread(() -> {

            try {
                Thread.sleep(1000 * arg.waitTime);

                System.out.println("Get request from " + arg.userName);
                syncPointA.await();

                System.out.println("Process request for " + arg.userName);
                syncPointB.await();

                System.out.println("Done " + arg.userName);
            }
            catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

        }).start());
    }



    private record ThreadArg(String userName, int waitTime) { }

}
