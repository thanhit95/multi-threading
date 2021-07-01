/*
 * SYNCHRONIZED
 * Version A: Synchronized block
 */

package demo14;

import java.util.stream.IntStream;



public class ProgramA {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new MyTaskA()).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + MyTaskA.counter);
        /*
         * We are sure that counter = 3000
         */
    }

}



class MyTaskA extends Thread {
    static int counter = 0;


    @Override
    public void run() {
        try { Thread.sleep(1000); } catch (InterruptedException e) { }

        /*
         * synchronized(this) means that on "this" object,
         *                    only and only one thread can excute the enclosed block at one time.
         *
         * "this" is the monitor object, the code inside the block gets synchronized on the monitor object.
         * Simply put, only one thread per monitor object can execute inside that block of code.
         */

        synchronized(this) {
            for (int i = 0; i < 1000; ++i) {
                ++counter;
            }
        }
    }
}
