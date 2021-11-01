/*
 * THREAD POOL
 * Version C02: Thread pool and Future
*/

package demo11;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;



public class AppC02 {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 2;
        final int NUM_TASKS = 5;


        ExecutorService executor = Executors.newFixedThreadPool(NUM_THREADS);


        // List<MyTask> todo
        var todo = IntStream.range(0, NUM_TASKS).mapToObj(i -> new MyTask((char)(i + 'A'))).toList();


        System.out.println("Begin to submit all tasks");
        /*
         * invokeAll() will not return until all the tasks are completed
         * (i.e., all the Futures in your answers collection will report isDone() if asked)
         *
         * List<Future<Character>> answers
         */
        var answers = executor.invokeAll(todo);


        System.out.println("All tasks are completed");
        executor.shutdown();


        answers.forEach(fut -> {
            try {
                System.out.println(fut.get());
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        });
    }

}



class MyTask implements Callable<Character> {
    char name;

    public MyTask(char name) {
        this.name = name;
    }

    @Override
    public Character call() throws Exception {
        try { Thread.sleep(1000); } catch (InterruptedException e) { }
        return name;
    }
}
