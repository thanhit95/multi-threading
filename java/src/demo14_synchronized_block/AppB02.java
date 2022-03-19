/*
 * SYNCHRONIZED BLOCKS
 * Version B02: Synchronized instance methods
 *
 * Assume there is a synchronized method "run" in object X:
 * Multiple threads associating with X should synchronize (block) when they execute method "run".
 *
 * If multiple threads associate with multiple objects (each thread ~ each object),
 *      they will NOT SYNCHRONIZE when execute method "run".
 *
 *      In demo code below, we create multiple Worker objects, so the problem happens.
 */

package demo14_synchronized_block;

import java.util.stream.IntStream;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 16;

        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new Worker()).toList();

        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();

        System.out.println("counter = " + Worker.counter);
        /*
         * We are NOT sure that counter = 16000
         */
    }



    private static class Worker extends Thread {
        public static int counter = 0;

        @Override
        public synchronized void run() {
            try { Thread.sleep(500); } catch (InterruptedException e) { }

            for (int i = 0; i < 1000; ++i) {
                ++counter;
            }
        }
    }

}
