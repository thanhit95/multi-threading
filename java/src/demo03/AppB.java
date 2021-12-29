/*
 * PASSING ARGUMENTS
 * Version B: Passing arguments to functions
 */

package demo03;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        var th1 = new Thread(() -> threadFunc(1, 2, "red"));
        var th2 = new Thread(() -> threadFunc(3, 4, "blue"));

        th1.start();
        th2.start();
    }


    private static void threadFunc(int a, double b, String c) {
        System.out.printf("%d  %.1f  %s %n", a, b, c);
    }

}
