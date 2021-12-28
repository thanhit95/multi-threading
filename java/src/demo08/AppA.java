/*
 * GETTING RETURNED VALUES FROM THREADS
 */

package demo08;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var th1 = new MyThread(5);
        var th2 = new MyThread(80);

        th1.start();
        th2.start();

        th1.join();
        th2.join();

        System.out.println(th1.result);
        System.out.println(th2.result);
    }

}



class MyThread extends Thread {
    int arg = 0;
    int result = 0;

    public MyThread(int arg) {
        super();
        this.arg = arg;
    }

    @Override
    public void run() {
        result = arg * 2;
    }
}
