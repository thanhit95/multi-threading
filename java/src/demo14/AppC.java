/*
 * SYNCHRONIZED BLOCKS
 * Version C: Synchronized static methods
 */

package demo14;

import java.util.stream.IntStream;



public class AppC {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 16;

        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new Worker()).toList();

        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();

        System.out.println("counter = " + Worker.counter);
        /*
         * We are sure that counter = 16000
         */
    }



    private static class Worker extends Thread {
        public static int counter = 0;

        @Override
        public void run() {
            incCounter();
        }

        private static synchronized void incCounter() {
            try { Thread.sleep(500); } catch (InterruptedException e) { }

            for (int i = 0; i < 1000; ++i) {
                ++counter;
            }
        }
    }

}
