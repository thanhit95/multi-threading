/*
 * THREAD POOL & EXECUTOR SERVICE IMPLEMENTATION
 */

package exer07;

import java.util.ArrayList;



public class App {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 2;
        final int NUM_TASKS = 5;


        var threadPool = new MyThreadPoolV2B();
        threadPool.init(NUM_THREADS);


        var lstTask = new ArrayList<MyTask>();

        for (int i = 0; i < NUM_TASKS; ++i)
            lstTask.add(new MyTask((char)('A' + i)));


        lstTask.forEach(task -> threadPool.submit(task));
        System.out.println("All tasks are submitted");


        threadPool.waitTaskDone();
        System.out.println("All tasks are completed");


        threadPool.shutdown();
    }



    static class MyTask implements Runnable {
        public char id;

        public MyTask(char id) {
            this.id = id;
        }

        @Override
        public void run() {
            System.out.println("Task " + id + " is starting");

            try {
                Thread.sleep(3000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("Task " + id + " is completed");
        }
    }

}
