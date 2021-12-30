/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A02: 2 slow producers, 1 fast consumer
 */

package exer02;

import java.util.concurrent.LinkedBlockingQueue;



public class AppA02 {

    public static void main(String[] args) {
        var qProduct = new LinkedBlockingQueue<Integer>();

        new Thread(() -> producer(qProduct)).start();
        new Thread(() -> producer(qProduct)).start();

        new Thread(() -> consumer(qProduct)).start();
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


    private static void consumer(LinkedBlockingQueue<Integer> qProduct) {
        for (;;) {
            try {
                int data = qProduct.take();
                System.out.println("Consumer " + data);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
