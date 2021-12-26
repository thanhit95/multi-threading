/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUE
 *      Version A03: 1 slow producer, 2 fast consumers
*/

package exer02;

import java.util.concurrent.LinkedBlockingQueue;



public class AppA03 {

    public static void main(String[] args) {
        var qProduct = new LinkedBlockingQueue<Integer>();

        new Thread(() -> funcProducer(qProduct)).start();

        new Thread(() -> funcConsumer("foo", qProduct)).start();
        new Thread(() -> funcConsumer("bar", qProduct)).start();
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


    private static void funcConsumer(String name, LinkedBlockingQueue<Integer> qProduct) {
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
