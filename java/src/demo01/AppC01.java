/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version C01: Using functions (via delegation from lambdas)
 */

package demo01;



public class AppC01 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(() -> doTask());

        th.start();

        System.out.println("Hello from main thread");
    }


    private static void doTask() {
        System.out.println("Hello from example thread");
    }

}
