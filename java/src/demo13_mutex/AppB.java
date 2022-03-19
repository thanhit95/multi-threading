/*
 * MUTEXES
 *
 * A binary semaphore can be used as a mutex.
 * Without synchronization (by a mutex), we are not sure that counter = 16000.
 */

package demo13_mutex;

import java.util.concurrent.Semaphore;
import java.util.stream.Stream;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 16;


        var lstTh = Stream.generate(() -> new Thread(() -> {

            try {
                Thread.sleep(1000);

                Global.mutex.acquire();

                for (int i = 0; i < 1000; ++i) {
                    Global.counter += 1;
                }

                Global.mutex.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

        })).limit(NUM_THREADS).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + Global.counter);
    }



    private static class Global {
        public static Semaphore mutex = new Semaphore(1);
        public static int counter = 0;
    }

}
