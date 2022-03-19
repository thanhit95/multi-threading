/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B01: Using inteface Runnable
 */

package demo01_hello;



public class AppB01 {

    public static void main(String[] args) throws InterruptedException {
        var doTask = new ExampleRunnable();

        var th1 = new Thread(doTask);
        var th2 = new Thread(doTask);

        th1.start();
        th2.start();

        System.out.println("Hello from main thread");
    }

}



class ExampleRunnable implements Runnable {
    @Override
    public void run() {
        System.out.println("Hello from example thread");
    }
}
