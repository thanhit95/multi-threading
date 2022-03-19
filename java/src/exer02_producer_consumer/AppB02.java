/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORES
 *      Version B02: 2 slow producers, 1 fast consumer
 */

package exer02_producer_consumer;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;



public class AppB02 {

    public static void main(String[] args) {
        var semFill = new Semaphore(0);     // item produced
        var semEmpty = new Semaphore(1);    // remaining space in queue

        Queue<Integer> queue = new LinkedList<>();

        new Thread(() -> producer(semFill, semEmpty, queue, 0)).start();
        new Thread(() -> producer(semFill, semEmpty, queue, 1000)).start();

        new Thread(() -> consumer(semFill, semEmpty, queue)).start();
    }


    private static void producer(Semaphore semFill, Semaphore semEmpty,
                                 Queue<Integer> queue, int startValue) {
        int i = 1;

        for (;; ++i) {
            try {
                semEmpty.acquire();

                queue.add(i + startValue);
                Thread.sleep(1000);

                semFill.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    private static void consumer(Semaphore semFill, Semaphore semEmpty, Queue<Integer> queue) {
        for (;;) {
            try {
                semFill.acquire();

                int data = queue.remove();
                System.out.println("Consumer " + data);

                semEmpty.release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
