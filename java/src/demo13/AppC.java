/*
 * SYNCHRONIZED
 * Version C: Synchronized static method
 */

package demo13;

import java.util.stream.IntStream;



public class AppC {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new MyTaskC()).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + MyTaskC.counter);
        /*
         * We are sure that counter = 30000
         */
    }

}



class MyTaskC extends Thread {
    static int counter = 0;


    @Override
    public void run() {
        incCounter();
    }


    private static synchronized void incCounter() {
        try { Thread.sleep(500); } catch (InterruptedException e) { }

        for (int i = 0; i < 10000; ++i) {
            ++counter;
        }
    }
}
