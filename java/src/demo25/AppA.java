/*
 * ATOMIC ACCESS
 */

package demo25;

import java.util.stream.IntStream;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        Runnable doTask = () -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }
            Global.counter += 1;
        };


        var lstTh = IntStream.range(0, 1000).mapToObj(i -> new Thread(doTask)).toList();


        for (var th : lstTh)
            th.start();


        for (var th : lstTh)
            th.join();


        // Unpredictable result
        System.out.println("counter = " + Global.counter);
    }



    class Global {
        public static volatile int counter = 0;
    }

}
