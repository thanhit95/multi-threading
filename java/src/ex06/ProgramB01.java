/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version B01: General blocking queue / underlying mechanism: semaphore
 */

package ex06;

import java.util.LinkedList;
import java.util.concurrent.Semaphore;



public class ProgramB01 {

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
        private Semaphore semRemain = null;
        private Semaphore semFill = null;

        @SuppressWarnings("unused")
        private int capacity = 0;

        private LinkedList<T> lst = null;


        public MyLinkedBlockingQueue(int capacity) {
            if (capacity <= 0)
                throw new IllegalArgumentException("capacity must be a positive integer");

            semRemain = new Semaphore(capacity);
            semFill = new Semaphore(0);

            this.capacity = capacity;
            lst = new LinkedList<T>();
        }


        public void put(T value) throws InterruptedException {
            semRemain.acquire();

            synchronized (lst) {
                lst.add(value);
            }

            semFill.release();
        }


        public T take() throws InterruptedException {
            T result = null;

            semFill.acquire();

            synchronized (lst) {
                result = lst.remove();
            }

            semRemain.release();

            return result;
        }
    }

}
