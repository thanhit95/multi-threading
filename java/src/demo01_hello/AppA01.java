/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A01: Using class Thread (original way)
 */

package demo01_hello;



public class AppA01 {

    public static void main(String[] args) throws InterruptedException {
        var th = new ExampleThread();
        th.start();
        System.out.println("Hello from main thread");
    }

}



class ExampleThread extends Thread {
    @Override
    public void run() {
        System.out.println("Hello from example thread");
    }
}
