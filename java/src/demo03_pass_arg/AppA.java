/*
 * PASSING ARGUMENTS
 * Version A: Passing arguments to Thread objects
 */

package demo03_pass_arg;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var thFoo = new MyThread(1, 2, "red");
        var thBar = new MyThread(3, 4, "blue");

        thFoo.start();
        thBar.start();
    }

}



class MyThread extends Thread {
    private int a;
    private double b;
    private String c;

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
