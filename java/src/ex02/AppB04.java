/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORE
 *      Version B04: Multiple fast producers, multiple slow consumers
*/

package ex02;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.stream.IntStream;



public class AppB04 {

    public static void main(String[] args) {
        var semFill = new Semaphore(0);     // item produced
        var semEmpty = new Semaphore(1);    // if remaining space in queue > 1 then error occurs

        Queue<Integer> qProduct = new LinkedList<>();


        final int NUM_PRODUCERS = 3;
        final int NUM_CONSUMERS = 2;


        IntStream.range(0, NUM_PRODUCERS).forEach(
                i -> new Thread(() -> funcProducer(semFill, semEmpty, qProduct, i * 1000)).start()
        );

        IntStream.range(0, NUM_CONSUMERS).forEach(
                i -> new Thread(() -> funcConsumer(semFill, semEmpty, qProduct)).start()
        );
    }


    private static void funcProducer(Semaphore semFill, Semaphore semEmpty,
                                     Queue<Integer> qProduct, int dataAddValue) {
        int i = 1;

        for (;; ++i) {
            try {
                semEmpty.acquire();

                qProduct.add(i + dataAddValue);

                semFill.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    private static void funcConsumer(Semaphore semFill, Semaphore semEmpty, Queue<Integer> qProduct) {
        for (;;) {
            try {
                semFill.acquire();

                System.out.println("queue remain: " + qProduct.size());

                int data = qProduct.remove();

                System.out.println("Consumer " + data);
                Thread.sleep(1000);

                semEmpty.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
