/*
 * BARRIERS
 * Version A: Cyclic barriers
 */

package demo18;

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
                Thread.sleep(1000 * arg.timeWait());

                System.out.println("Get request from " + arg.userName());

                syncPointA.await();

                System.out.println("Process request for " + arg.userName());

                syncPointB.await();

                System.out.println("Done " + arg.userName());
            }
            catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

        }).start());
    }



    record ThreadArg(String userName, int timeWait) { }

}
