/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A02: 2 slow producers, 1 fast consumer
 */

package exer02_producer_consumer;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;



public class AppA02 {

    public static void main(String[] args) {
        var queue = new LinkedBlockingQueue<Integer>();

        new Thread(() -> producer(queue)).start();
        new Thread(() -> producer(queue)).start();

        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(BlockingQueue<Integer> queue) {
        int i = 1;

        for (;; ++i) {
            try {
                queue.put(i);
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    private static void consumer(BlockingQueue<Integer> queue) {
        for (;;) {
            try {
                int data = queue.take();
                System.out.println("Consumer " + data);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
