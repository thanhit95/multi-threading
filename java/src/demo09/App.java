/*
 * THREAD DETACHING
 */

package demo09;



public class App {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(() -> {
            System.out.println("Thread is starting...");

            try { Thread.sleep(2000); } catch (InterruptedException e) { }

            System.out.println("Thread is exiting...");
        });


        th.setDaemon(true);
        th.start();


        // If I comment this statement,
        // th will be forced into terminating with main thread
        Thread.sleep(3000);


        System.out.println("Program is terminating");
    }

}
