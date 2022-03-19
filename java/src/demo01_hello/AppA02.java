/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A02: Using class Thread (anonymous subclass)
 */

package demo01_hello;



public class AppA02 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread() {
            @Override
            public void run() {
                System.out.println("Hello from example thread");
            }
        };

        th.start();

        System.out.println("Hello from main thread");
    }

}
