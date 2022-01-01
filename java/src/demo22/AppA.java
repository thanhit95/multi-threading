/*
 * BLOCKING QUEUES
 * Version A: A slow producer and a fast consumer
 */

package demo22;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;



public class AppA {

    public static void main(String[] args) {
        BlockingQueue<String> queue;

        queue = new LinkedBlockingQueue<>();
        // queue = new ArrayBlockingQueue<>(2); // blocking queue with capacity = 2

        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(BlockingQueue<String> queue) {
        try {
            Thread.sleep(2000);
            queue.put("Alice");

            Thread.sleep(2000);
            queue.put("likes");

            Thread.sleep(2000);
            queue.put("singing");
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    private static void consumer(BlockingQueue<String> queue) {
        String data = "";

        try {
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
