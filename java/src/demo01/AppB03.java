/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B03: Using inteface Runnable with lambdas
 */

package demo01;



public class AppB03 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(() -> System.out.println("Hello from example thread"));

        th.start();

        System.out.println("Hello from main thread");
    }

}
