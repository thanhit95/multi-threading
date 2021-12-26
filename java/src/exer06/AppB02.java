/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version B02: General blocking queue / underlying mechanism: condition variable
 */

package exer06;

import java.util.LinkedList;



public class AppB02 {

    public static void main(String[] args) {
        final var queue = new MyLinkedBlockingQueue<String>(2); // capacity = 2
        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(MyLinkedBlockingQueue<String> queue) {
        String[] arr = { "nice", "to", "meet", "you" };

        try {
            for (var value : arr) {
                queue.put(value);
                System.out.println("Producer: " + value + "\t\t\t[done]");
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    private static void consumer(MyLinkedBlockingQueue<String> queue) {
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


    static class MyLinkedBlockingQueue<T> {
        private Object condEmpty = new Object();
        private Object condFull = new Object();

        private int capacity = 0;
        private LinkedList<T> lst = null;


        public MyLinkedBlockingQueue(int capacity) {
            if (capacity <= 0)
                throw new IllegalArgumentException("capacity must be a positive integer");

            this.capacity = capacity;
            lst = new LinkedList<T>();
        }


        public void put(T value) throws InterruptedException {
            synchronized (condFull) {
                while (capacity == lst.size()) {
                    // queue is full, must wait for 'take'
                    condFull.wait();
                }
            }

            synchronized (lst) {
                lst.add(value);
            }

            synchronized (condEmpty) {
                condEmpty.notify();
            }
        }


        public T take() throws InterruptedException {
            T result = null;

            synchronized (condEmpty) {
                while (0 == lst.size()) {
                    // queue is empty, must wait for 'put'
                    condEmpty.wait();
                }
            }

            synchronized (lst) {
                result = lst.remove();
            }

            synchronized (condFull) {
                condFull.notify();
            }

            return result;
        }
    }

}
