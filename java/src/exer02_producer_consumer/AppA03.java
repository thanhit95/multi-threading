/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A03: 1 slow producer, 2 fast consumers
 */

package exer02_producer_consumer;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;



public class AppA03 {

    public static void main(String[] args) {
        var queue = new LinkedBlockingQueue<Integer>();

        new Thread(() -> producer(queue)).start();

        new Thread(() -> consumer("foo", queue)).start();
        new Thread(() -> consumer("bar", queue)).start();
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


    private static void consumer(String name, BlockingQueue<Integer> queue) {
        for (;;) {
            try {
                int data = queue.take();
                System.out.println("Consumer %s: %d".formatted(name, data));
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
