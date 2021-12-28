/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B01: Using inteface Runnable
*/

package demo01;



public class AppB01 {

    public static void main(String[] args) throws InterruptedException {
        var runnable = new LoremRunnable();

        var th1 = new Thread(runnable);
        var th2 = new Thread(runnable);

        th1.start();
        th2.start();

        System.out.println("Hello from main thread");
    }

}



class LoremRunnable implements Runnable {
    @Override
    public void run() {
        System.out.println("Hello from Lorem thread");
    }
}
