/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B02: Using inteface Runnable with lambdas
 */

package demo01;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException {
        Runnable runnable = () -> System.out.println("Hello from Lorem thread");

        var th1 = new Thread(runnable);
        var th2 = new Thread(runnable);

        th1.start();
        th2.start();

        System.out.println("Hello from main thread");
    }

}
