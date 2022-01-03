/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version A: Synchronous queues
 */

package exer06;

import java.util.concurrent.Semaphore;



public class AppA {

    public static void main(String[] args) {
        final var queue = new MySynchronousQueue<String>();
        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(MySynchronousQueue<String> queue) {
        String[] arr = { "lorem", "ipsum", "dolor" };

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


    private static void consumer(MySynchronousQueue<String> queue) {
        String data = "";

        try {
            Thread.sleep(5000);

            for (int i = 0; i < 3; ++i) {
                data = queue.take();
                System.out.println("\tConsumer: " + data);
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    private static class MySynchronousQueue<T> {
        private Semaphore semPut = new Semaphore(1);
        private Semaphore semTake = new Semaphore(0);
        private T element = null;


        public void put(T value) throws InterruptedException {
            semPut.acquire();
            element = value;
            semTake.release();
        }


        public T take() throws InterruptedException {
            semTake.acquire();

            T result = element;
            element = null;

            semPut.release();

            return result;
        }
    }

}
