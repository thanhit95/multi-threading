/*
 * MUTEXES
 *
 * A binary semaphore can be used as a mutex.
 * Without synchronization (by a mutex), we are not sure that result = 30000.
 */

package demo13;

import java.util.concurrent.Semaphore;
import java.util.stream.Stream;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;

        var lstTh = Stream.generate(() -> new Thread(() -> doTask()))
                .limit(NUM_THREADS)
                .toList();

        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();

        System.out.println("counter = " + Global.counter);
    }


    private static void doTask() {
        try {
            Thread.sleep(1000);

            Global.mutex.acquire();

            for (int i = 0; i < 10000; ++i)
                ++Global.counter;

            Global.mutex.release();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    private static class Global {
        public static Semaphore mutex = new Semaphore(1);
        public static int counter = 0;
    }

}
