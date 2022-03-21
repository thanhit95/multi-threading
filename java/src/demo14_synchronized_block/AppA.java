/*
 * SYNCHRONIZED BLOCKS
 * Version A: Synchronized blocks
 */

package demo14_synchronized_block;

import java.util.stream.IntStream;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 16;

        var worker = new MyTask();

        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new Thread(worker)).toList();

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
        public void run() {
            try { Thread.sleep(500); } catch (InterruptedException e) { }

            /*
             * synchronized (this) means that on "this" object,
             *                    only and only one thread can execute the enclosed block at one time.
             *
             * "this" is the monitor object, the code inside the block gets synchronized on the monitor object.
             * Simply put, only one thread per monitor object can execute inside that block of code.
             */

            synchronized (this) {
                for (int i = 0; i < 1000; ++i) {
                    ++counter;
                }
            }
        }
    }

}
