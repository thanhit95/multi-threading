/*
 * GETTING RETURNED VALUES FROM THREADS
 */

package demo08;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var thFoo = new MyThread(5);
        var thBar = new MyThread(80);

        thFoo.start();
        thBar.start();

        thFoo.join();
        thBar.join();

        System.out.println(thFoo.result);
        System.out.println(thBar.result);
    }

}



class MyThread extends Thread {
    public int arg = 0;
    public int result = 0;

    public MyThread(int arg) {
        super();
        this.arg = arg;
    }

    @Override
    public void run() {
        result = arg * 2;
    }
}
