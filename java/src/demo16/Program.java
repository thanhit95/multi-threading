/*
 * MONITOR
*/

package demo16;

import java.util.stream.IntStream;



public class Program {

    public static void main(String[] args) throws InterruptedException {
        var counter = new Counter();

        var monitor = new Monitor();
        monitor.init(counter);

        final int NUM_THREADS = 3;


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



class Monitor {
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
