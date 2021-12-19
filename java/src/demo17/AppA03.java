/*
 * BARRIER
 * Version A: Cyclic barrier
*/

package demo17;

import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;



public class AppA03 {

    public static void main(String[] args) {
        var syncPointA = new CyclicBarrier(2);
        var syncPointB = new CyclicBarrier(2);


        var lstArgs = List.of(
                new ThreadArg("foo", 1),
                new ThreadArg("bar", 3),
                new ThreadArg("ham", 3),
                new ThreadArg("egg", 10)
        );


        lstArgs.forEach(arg -> new Thread(() -> {

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
