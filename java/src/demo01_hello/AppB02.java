/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B02: Using inteface Runnable with lambdas
 */

package demo01_hello;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException {
        Runnable doTask = () -> System.out.println("Hello from example thread");

        var th1 = new Thread(doTask);
        var th2 = new Thread(doTask);

        th1.start();
        th2.start();

        System.out.println("Hello from main thread");
    }

}
