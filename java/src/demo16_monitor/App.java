/*
 * MONITORS
 * Implementation of a monitor for managing a counter
 */

package demo16_monitor;

import java.util.stream.IntStream;



public class App {

    public static void main(String[] args) throws InterruptedException {
        var counter = new Counter();
        var monitor = new MyMonitor();
        monitor.init(counter);

        final int NUM_THREADS = 16;


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(t -> new Thread(() -> {

            try { Thread.sleep(1000); } catch (InterruptedException e) { }

            for (int i = 0; i < 1000; ++i)
                monitor.increaseCounter();

        })).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        System.out.println("counter = " + counter.value);
    }

}



class Counter {
    public int value = 0;
}



class MyMonitor {
    private Counter counter = null;

    public void init(Counter counter) {
        this.counter = counter;
    }

    public void increaseCounter() {
        synchronized (counter) {
            ++counter.value;
        }
    }
}
