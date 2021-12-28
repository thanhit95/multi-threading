/*
 * BARRIER
 * Version A: Cyclic barrier
*/

package demo18;

import java.util.List;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;



public class AppA02 {

    public static void main(String[] args) {
        var syncPoint = new CyclicBarrier(2); // participant count = 2


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

                syncPoint.await();

                System.out.println("Process request for " + arg.userName());

                syncPoint.await();

                System.out.println("Done " + arg.userName());
            }
            catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }

        }).start());


        // thread "egg" will be FREEZED
    }



    record ThreadArg(String userName, int timeWait) { }

}
