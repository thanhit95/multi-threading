/*
 * THREAD-LOCAL STORAGE
 * Avoiding synchronization using thread-local storage
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


        lstTh.forEach(Thread::start);


        /*
         * By using thread-local storage, each thread has its own counter.
         * So, the counter in one thread is completely independent of each other.
         *
         * Thread-local storage helps us to AVOID SYNCHRONIZATION.
         */
    }



    private static class Counter {
        public int value = 0;
    }



    private static class MyTask {
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
