/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A01: Using class Thread / Stanrd way
*/

package demo01a;



public class Program01 {

    public static void main(String[] args) throws InterruptedException {
        var th1 = new HelloThread();
        var th2 = new HelloThread();

        th1.start();
        th2.start();

        th1.join();
        th2.join();
    }

}



class HelloThread extends Thread {
    @Override
    public void run() {
        System.out.println("Hello");
    }
}
