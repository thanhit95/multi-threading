/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A04: Multiple fast producers, multiple slow consumers
 */

package exer02;

import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.IntStream;



public class AppA04 {

    public static void main(String[] args) {
        var qProduct = new LinkedBlockingQueue<Integer>();


        final int NUM_PRODUCERS = 3;
        final int NUM_CONSUMERS = 2;


        IntStream.range(0, NUM_PRODUCERS).forEach(
                i -> new Thread(() -> producer(qProduct, i * 1000)).start()
        );

        IntStream.range(0, NUM_CONSUMERS).forEach(
                i -> new Thread(() -> consumer(qProduct)).start()
        );
    }


    private static void producer(LinkedBlockingQueue<Integer> qProduct, int startValue) {
        int i = 1;

        for (;; ++i) {
            qProduct.add(i + startValue);
        }
    }


    private static void consumer(LinkedBlockingQueue<Integer> qProduct) {
        for (;;) {
            int data = qProduct.remove();
            System.out.println("Consumer " + data);
            try { Thread.sleep(1000); } catch (InterruptedException e) { }
        }
    }

}
