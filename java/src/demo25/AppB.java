/*
 * ATOMIC
*/

package demo25;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        Runnable routine = () -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }
            Global.counter.incrementAndGet();
            // Global.counter.addAndGet(1);
        };


        var lstTh = IntStream.range(0, 1000).mapToObj(i -> new Thread(routine)).toList();


        for (var th : lstTh)
            th.start();


        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + Global.counter); // counter = 1000
    }



    class Global {
        public static AtomicInteger counter = new AtomicInteger(0);
    }

}
