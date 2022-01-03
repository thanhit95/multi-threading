/*
 * ATOMIC ACCESS
 */

package demo25;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        Runnable doTask = () -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }
            Global.counter.incrementAndGet();
            // Global.counter.addAndGet(1);
        };


        var lstTh = IntStream.range(0, 1000).mapToObj(i -> new Thread(doTask)).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        // counter = 1000
        System.out.println("counter = " + Global.counter);
    }



    private static class Global {
        public static AtomicInteger counter = new AtomicInteger(0);
    }

}
