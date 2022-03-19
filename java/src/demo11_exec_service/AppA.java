/*
 * EXECUTOR SERVICES AND THREAD POOLS
 * Version A: The executor service (of which thread pool) containing a single thread
 *
 * Note: The single thread executor is ideal for creating an event loop.
 */

package demo11_exec_service;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;



public class AppA {

    public static void main(String[] args) {
        ExecutorService executor = Executors.newSingleThreadExecutor();

        executor.submit(() -> System.out.println("Hello World"));
        executor.submit(() -> System.out.println("Hello Multithreading"));

        Runnable rnn = () -> System.out.println("Hello the Executor Service");
        executor.submit(rnn);

        executor.shutdown();
    }

}
