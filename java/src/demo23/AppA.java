/*
 * THREAD-LOCAL STORAGE
 * The basic way to use thread-local storage.
*/

package demo23;

import java.util.stream.IntStream;



public class AppA {

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
        public static ThreadLocal<Counter> thlCounter = new ThreadLocal<>();

        public static void increaseCounter() {
            Counter counter = thlCounter.get();

            if (null == counter) {
                // first time getting counter in a thread
                counter = new Counter();
                thlCounter.set(counter);
            }

            ++counter.value;
        }
    }

}
