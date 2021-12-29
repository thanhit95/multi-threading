/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B04: Using functions (via delegation from lambdas)
 */

package demo01;



public class AppB04 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(() -> threadFunc());

        th.start();

        System.out.println("Hello from main thread");
    }


    private static void threadFunc() {
        System.out.println("Hello from example thread");
    }

}
