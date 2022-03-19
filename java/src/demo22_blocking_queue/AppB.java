/*
 * BLOCKING QUEUES
 * Version B: A fast producer and a slow consumer
 */

package demo22_blocking_queue;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;



public class AppB {

    public static void main(String[] args) {
        BlockingQueue<String> queue;
        queue = new ArrayBlockingQueue<>(2); // blocking queue with capacity = 2

        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(BlockingQueue<String> queue) {
        try {
            queue.put("Alice");
            queue.put("likes");

            /*
             * Due to reaching the maximum capacity = 2, when executing queue.put("singing"),
             * this thread is going to sleep until the queue removes an element.
             */

            queue.put("singing");
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    private static void consumer(BlockingQueue<String> queue) {
        String data;

        try {
            Thread.sleep(2000);

            for (int i = 0; i < 3; ++i) {
                System.out.println("\nWaiting for data...");

                data = queue.take();

                System.out.println("    " + data);
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
