/*
 * SYNCHRONIZED BLOCKS
 * Version B01: Synchronized instance methods
 */

package demo14_synchronized_block;

import java.util.stream.IntStream;



public class AppB01 {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 16;

        var myTask = new MyTask();

        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new Thread(myTask)).toList();

        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();

        System.out.println("counter = " + MyTask.counter);
        /*
         * We are sure that counter = 16000
         */
    }



    private static class MyTask implements Runnable {
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
