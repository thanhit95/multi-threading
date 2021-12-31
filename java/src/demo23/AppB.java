/*
 * THREAD-LOCAL STORAGE
 * Avoiding synchronization using Thread-Local Storage
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

            System.out.println("Thread " + t + " gives counter = " + MyTask.getCounter());
        })).toList();


        for (var th : lstTh)
            th.start();


        /*
         * By using Thread-Local Storage, each thread has its own counter.
         * So, the counter in one thread is completely independent of each other.
         *
         * Thread-Local Storage helps us to AVOID SYNCHRONIZATION.
         */
    }



    static class Counter {
        public int value = 0;
    }



    static class MyTask {
        private static ThreadLocal<Counter> thlCounter = ThreadLocal.withInitial(() -> new Counter());

        public static int getCounter() {
            return thlCounter.get().value;
        }

        public static void increaseCounter() {
            var counter = thlCounter.get();
            ++counter.value;
        }
    }

}
