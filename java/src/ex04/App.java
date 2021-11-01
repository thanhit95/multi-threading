/*
 * THE DINING PHILOSOPHERS PROBLEM
 */

package ex04;

import java.util.concurrent.Semaphore;
import java.util.stream.IntStream;



public class App {

    public static void main(String[] args) {
        final int NUM_PHILOSOPHERS = 5;


        var chopstick = new Semaphore[NUM_PHILOSOPHERS];

        for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
            chopstick[i] = new Semaphore(1);


        var lstTh = IntStream.range(0, NUM_PHILOSOPHERS).mapToObj(i -> new Thread(() -> {

            int n = NUM_PHILOSOPHERS;

            try {
                Thread.sleep(1000);

                chopstick[i].acquire();
                chopstick[(i + 1) % n].acquire();

                System.out.println("Philosopher #" + i + " is eating the rice");

                chopstick[(i + 1) % n].release();
                chopstick[i].release();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

        }));


        lstTh.forEach(Thread::start);
    }

}
