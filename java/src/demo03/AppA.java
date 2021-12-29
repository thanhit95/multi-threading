/*
 * PASSING ARGUMENTS
 * Version A: Passing arguments to Thread objects
 */

package demo03;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var foo = new MyThread(1, 2, "red");
        var bar = new MyThread(3, 4, "blue");

        foo.start();
        bar.start();
    }

}



class MyThread extends Thread {
    int a;
    double b;
    String c;

    public MyThread(int a, double b, String c) {
        super();
        this.a = a;
        this.b = b;
        this.c = c;
    }

    @Override
    public void run() {
        System.out.printf("%d  %.1f  %s %n", a, b, c);
    }
}
