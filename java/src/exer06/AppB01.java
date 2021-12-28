/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version B01: General blocking queues
 *              Underlying mechanism: Semaphores
 */

package exer06;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;



public class AppB01 {

    public static void main(String[] args) {
        final var queue = new MyBlockingQueue<String>(2); // capacity = 2
        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(MyBlockingQueue<String> queue) {
        String[] arr = { "nice", "to", "meet", "you" };

        try {
            for (var value : arr) {
                System.out.println("Producer: " + value);
                queue.put(value);
                System.out.println("Producer: " + value + "\t\t\t[done]");
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    private static void consumer(MyBlockingQueue<String> queue) {
        String data = "";

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


    static class MyBlockingQueue<T> {
        private Semaphore semRemain = null;
        private Semaphore semFill = null;

        @SuppressWarnings("unused")
        private int capacity = 0;

        private Queue<T> queue = null;


        public MyBlockingQueue(int capacity) {
            if (capacity <= 0)
                throw new IllegalArgumentException("capacity must be a positive integer");

            semRemain = new Semaphore(capacity);
            semFill = new Semaphore(0);

            this.capacity = capacity;
            queue = new LinkedList<T>();
        }


        public void put(T value) throws InterruptedException {
            semRemain.acquire();

            synchronized (queue) {
                queue.add(value);
            }

            semFill.release();
        }


        public T take() throws InterruptedException {
            T result = null;

            semFill.acquire();

            synchronized (queue) {
                result = queue.remove();
            }

            semRemain.release();

            return result;
        }
    }

}
