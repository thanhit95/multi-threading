/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B01: Using inteface Runnable / Standard way
*/

package demo01;



public class AppB01 {

    public static void main(String[] args) throws InterruptedException {
        var runnable = new MyRunnable();

        var th1 = new Thread(runnable);
        var th2 = new Thread(runnable);

        th1.start();
        th2.start();

        th1.join();
        th2.join();
    }

}



class MyRunnable implements Runnable {
    @Override
    public void run() {
        System.out.println("Hello");
    }
}
