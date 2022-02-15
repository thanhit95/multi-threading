/*
 * RACE CONDITIONS AND DATA RACES
 */

package demo12;

import java.util.stream.Stream;



public class AppC01 {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 16;


        var lstTh = Stream.generate(() -> new Thread(() -> {

            try { Thread.sleep(1000); } catch (InterruptedException e) { }

            for (int i = 0; i < 1000; ++i) {
                Global.counter += 1;
            }

        })).limit(NUM_THREADS).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + Global.counter);
        /*
         * We are not sure that counter = 16000
         */
    }



    private static class Global {
        public static int counter = 0;
    }

}
