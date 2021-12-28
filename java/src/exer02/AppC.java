/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE C: USING CONDITION VARIABLES & MONITORS
 *      Multiple fast producers, multiple slow consumers
 */

package exer02;

import java.util.LinkedList;
import java.util.Queue;
import java.util.stream.IntStream;



public class AppC {

    public static void main(String[] args) {
        var monitor = new Monitor<Integer>();
        Queue<Integer> qProduct = new LinkedList<>();


        final int MAX_QUEUE_SIZE = 6;
        final int NUM_PRODUCERS = 3;
        final int NUM_CONSUMERS = 2;


        monitor.init(MAX_QUEUE_SIZE, qProduct);


        IntStream.range(0, NUM_PRODUCERS).forEach(
                i -> new Thread(() -> funcProducer(monitor, i * 1000)).start()
        );

        IntStream.range(0, NUM_CONSUMERS).forEach(
                i -> new Thread(() -> funcConsumer(monitor)).start()
        );
    }


    private static void funcProducer(Monitor<Integer> monitor, int startValue) {
        int i = 1;

        for (;; ++i) {
            try {
                monitor.add(i + startValue);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    private static void funcConsumer(Monitor<Integer> monitor) {
        for (;;) {
            try {
                int data = monitor.remove();
                System.out.println("Consumer " + data);
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}



class Monitor<T> {
    private Queue<T> q;
    private int maxQueueSize;

    private Object condFull = new Object();
    private Object condEmpty = new Object();


    public void init(int maxQueueSize, Queue<T> q ) {
        this.maxQueueSize = maxQueueSize;
        this.q = q;
    }


    public void add(T item) throws InterruptedException {
        synchronized (condFull) {
            while (q.size() == maxQueueSize) {
                condFull.wait();
            }

            q.add(item);
        }

        synchronized (condEmpty) {
            if (q.size() == 1) {
                condEmpty.notify();
            }
        }
    }


    public T remove() throws InterruptedException {
        T item = null;

        synchronized (condEmpty) {
            while (q.size() == 0) {
                condEmpty.wait();
            }

            item = q.remove();
        }

        synchronized (condFull) {
            if (q.size() == maxQueueSize - 1) {
                condFull.notify();
            }
        }

        return item;
    }
}
