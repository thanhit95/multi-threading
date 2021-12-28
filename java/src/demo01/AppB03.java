/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B03: Using inteface Runnable with lambda
 */

package demo01;



public class AppB03 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(() -> System.out.println("Hello from Lorem thread"));

        th.start();

        System.out.println("Hello from main thread");
    }

}
