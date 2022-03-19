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
        var monitor = new ProdConsMonitor<Integer>();
        Queue<Integer> queue = new LinkedList<>();


        final int MAX_QUEUE_SIZE = 6;
        final int NUM_PRODUCERS = 3;
        final int NUM_CONSUMERS = 2;


        monitor.init(MAX_QUEUE_SIZE, queue);


        IntStream.range(0, NUM_PRODUCERS).forEach(
                i -> new Thread(() -> producer(monitor, i * 1000)).start()
        );

        IntStream.range(0, NUM_CONSUMERS).forEach(
                i -> new Thread(() -> consumer(monitor)).start()
        );
    }


    private static void producer(ProdConsMonitor<Integer> monitor, int startValue) {
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


    private static void consumer(ProdConsMonitor<Integer> monitor) {
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



class ProdConsMonitor<T> {
    private Queue<T> queue;
    private int maxQueueSize;

    private Object condFull = new Object();
    private Object condEmpty = new Object();


    public void init(int maxQueueSize, Queue<T> queue) {
        this.maxQueueSize = maxQueueSize;
        this.queue = queue;
    }


    public void add(T item) throws InterruptedException {
        synchronized (condFull) {
            while (queue.size() == maxQueueSize) {
                condFull.wait();
            }

            synchronized (queue) {
                queue.add(item);
            }
        }

        synchronized (condEmpty) {
            if (queue.size() == 1) {
                condEmpty.notify();
            }
        }
    }


    public T remove() throws InterruptedException {
        T item = null;

        synchronized (condEmpty) {
            while (queue.size() == 0) {
                condEmpty.wait();
            }

            synchronized (queue) {
                item = queue.remove();
            }
        }

        synchronized (condFull) {
            if (queue.size() == maxQueueSize - 1) {
                condFull.notify();
            }
        }

        return item;
    }
}
