/*
 * THE DINING PHILOSOPHERS PROBLEM
 */

package exer04_dining_philosophers;

import java.util.stream.IntStream;



public class AppB {

    public static void main(String[] args) {
        final int NUM_PHILOSOPHERS = 5;


        var chopstick = new Object[NUM_PHILOSOPHERS];

        for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
            chopstick[i] = new Object();


        var lstTh = IntStream.range(0, NUM_PHILOSOPHERS).mapToObj(i -> new Thread(() -> {

            int n = NUM_PHILOSOPHERS;

            try {
                Thread.sleep(1000);

                synchronized (chopstick[i]) {
                    synchronized (chopstick[(i + 1) % n]) {
                        System.out.println("Philosopher #" + i + " is eating the rice");
                    }
                }
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

        }));


        lstTh.forEach(Thread::start);
    }

}
