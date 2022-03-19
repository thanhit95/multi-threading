/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version C02: Using function references
 */

package demo01_hello;



public class AppC02 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(AppC02::doTask);

        th.start();

        System.out.println("Hello from main thread");
    }


    private static void doTask() {
        System.out.println("Hello from example thread");
    }

}
