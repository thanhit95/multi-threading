/*
 * THREAD-LOCAL STORAGE
 * Use ThreadLocal.withInitial for better initialization.
*/

package demo23;

import java.util.stream.IntStream;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(t -> new Thread(() -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }

            for (int i = 0; i < 1000; ++i)
                MyTask.increaseCounter();

            System.out.println("Thread " + t + " gives counter = " + MyTask.thlCounter.get().value);
        })).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        /*
         * By using thread-local storage, each thread has its own counter.
         * So, the counter in one thread is completely independent of each other.
         *
         * Thread-local storage helps us to AVOID SYNCHRONIZATION.
         */
    }



    static class Counter {
        public int value = 0;
    }



    static class MyTask {
        public static ThreadLocal<Counter> thlCounter = ThreadLocal.withInitial(() -> {
            return new Counter();
        });

        public static void increaseCounter() {
            Counter counter = thlCounter.get();
            ++counter.value;
        }
    }

}
