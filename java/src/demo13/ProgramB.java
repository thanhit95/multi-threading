/*
 * MUTEX (Mutual Exclusion)
 *
 * A binary semaphore can be used as a mutex.
 *
 * If you do not synchronize (by a mutex), we are not sure that result = 30000
 */

package demo13;

import java.util.concurrent.Semaphore;
import java.util.stream.Stream;



public class ProgramB {

    public static void main(String[] args) throws InterruptedException {
        var mutex = new Semaphore(1);


        Runnable routineCounter = () -> {
            try {
                Thread.sleep(1000);

                mutex.acquire();

                for (int i = 0; i < 10000; ++i)
                    ++Global.counter;

                mutex.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        };


        final int NUM_THREADS = 3;


        var lstTh = Stream.generate(() -> new Thread(routineCounter)).limit(NUM_THREADS).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + Global.counter);
    }



    class Global {
        public static int counter = 0;
    }

}
