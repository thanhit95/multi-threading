/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A04: Multiple fast producers, multiple slow consumers
 */

package exer02_producer_consumer;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.stream.IntStream;



public class AppA04 {

    public static void main(String[] args) {
        var queue = new ArrayBlockingQueue<Integer>(5);


        final int NUM_PRODUCERS = 3;
        final int NUM_CONSUMERS = 2;


        IntStream.range(0, NUM_PRODUCERS).forEach(
                i -> new Thread(() -> producer(queue, i * 1000)).start()
        );

        IntStream.range(0, NUM_CONSUMERS).forEach(
                i -> new Thread(() -> consumer(queue)).start()
        );
    }


    private static void producer(BlockingQueue<Integer> queue, int startValue) {
        int i = 1;

        for (;; ++i) {
            try {
                queue.put(i + startValue);
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
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
