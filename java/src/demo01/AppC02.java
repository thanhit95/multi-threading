/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version C02: Using function references
 */

package demo01;



public class AppC02 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(AppC02::threadFunc);

        th.start();

        System.out.println("Hello from main thread");
    }


    private static void threadFunc() {
        System.out.println("Hello from example thread");
    }

}
