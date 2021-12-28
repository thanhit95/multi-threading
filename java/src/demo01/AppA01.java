/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A01: Using class Thread (original way)
 */

package demo01;



public class AppA01 {

    public static void main(String[] args) throws InterruptedException {
        var th = new LoremThread();
        th.start();
        System.out.println("Hello from main thread");
    }

}



class LoremThread extends Thread {
    @Override
    public void run() {
        System.out.println("Hello from Lorem thread");
    }
}
