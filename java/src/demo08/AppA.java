/*
 * GETTING RETURNED VALUES FROM THREADS
 */

package demo08;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var foo = new MyThread(5);
        var bar = new MyThread(80);

        foo.start();
        bar.start();

        foo.join();
        bar.join();

        System.out.println(foo.result);
        System.out.println(bar.result);
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
