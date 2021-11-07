/*
 * ATOMIC
*/

package demo24;

import java.util.stream.IntStream;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        Runnable routine = () -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }
            Global.counter += 1;
        };


        var lstTh = IntStream.range(0, 1000).mapToObj(i -> new Thread(routine)).toList();


        for (var th : lstTh)
            th.start();


        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + Global.counter); // unpredictable result
    }



    class Global {
        public static volatile int counter = 0;
    }

}
