/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version B02: General blocking queues
 *              Underlying mechanism: Condition variables
 */

package exer06_blocking_queue;

import java.util.LinkedList;
import java.util.Queue;



public class AppB02 {

    public static void main(String[] args) {
        final var queue = new MyBlockingQueue<String>(2); // capacity = 2
        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(MyBlockingQueue<String> queue) {
        String[] arr = { "nice", "to", "meet", "you" };

        try {
            for (var data : arr) {
                System.out.println("Producer: " + data);
                queue.put(data);
                System.out.println("Producer: " + data + "\t\t\t[done]");
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    private static void consumer(MyBlockingQueue<String> queue) {
        String data;

        try {
            Thread.sleep(5000);

            for (int i = 0; i < 4; ++i) {
                data = queue.take();
                System.out.println("\tConsumer: " + data);

                if (0 == i)
                    Thread.sleep(5000);
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    //////////////////////////////////////////////


    private static class MyBlockingQueue<T> {
        private final Object condEmpty = new Object();
        private final Object condFull = new Object();

        private int capacity = 0;
        private final Queue<T> queue;


        public MyBlockingQueue(int capacity) {
            if (capacity <= 0)
                throw new IllegalArgumentException("capacity must be a positive integer");

            this.capacity = capacity;
            queue = new LinkedList<T>();
        }


        public void put(T value) throws InterruptedException {
            synchronized (condFull) {
                while (queue.size() >= capacity) {
                    // Queue is full, must wait for 'take'
                    condFull.wait();
                }

                synchronized (queue) {
                    queue.add(value);
                }
            }

            synchronized (condEmpty) {
                condEmpty.notify();
            }
        }


        public T take() throws InterruptedException {
            T result;

            synchronized (condEmpty) {
                while (queue.isEmpty()) {
                    // Queue is empty, must wait for 'put'
                    condEmpty.wait();
                }

                synchronized (queue) {
                    result = queue.remove();
                }
            }

            synchronized (condFull) {
                condFull.notify();
            }

            return result;
        }
    }

}
