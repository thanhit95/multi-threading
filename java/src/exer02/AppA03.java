/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A03: 1 slow producer, 2 fast consumers
 */

package exer02;

import java.util.concurrent.LinkedBlockingQueue;



public class AppA03 {

    public static void main(String[] args) {
        var qProduct = new LinkedBlockingQueue<Integer>();

        new Thread(() -> producer(qProduct)).start();

        new Thread(() -> consumer("foo", qProduct)).start();
        new Thread(() -> consumer("bar", qProduct)).start();
    }


    private static void producer(LinkedBlockingQueue<Integer> qProduct) {
        int i = 1;

        for (;; ++i) {
            try {
                qProduct.put(i);
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    private static void consumer(String name, LinkedBlockingQueue<Integer> qProduct) {
        for (;;) {
            try {
                int data = qProduct.take();
                System.out.println("Consumer %s: %d".formatted(name, data));
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
