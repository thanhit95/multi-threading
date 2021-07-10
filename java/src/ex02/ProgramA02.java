/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUE
 *      Version A02: 2 slow producers, 1 fast consumer
*/

package ex02;

import java.util.concurrent.LinkedBlockingQueue;



public class ProgramA02 {

    public static void main(String[] args) {
        var qProduct = new LinkedBlockingQueue<Integer>();

        new Thread(() -> funcProducer(qProduct)).start();
        new Thread(() -> funcProducer(qProduct)).start();

        new Thread(() -> funcConsumer(qProduct)).start();
    }


    private static void funcProducer(LinkedBlockingQueue<Integer> qProduct) {
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


    private static void funcConsumer(LinkedBlockingQueue<Integer> qProduct) {
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
