/*
 * PASSING ARGUMENTS
 * Version B: Passing arguments to functions
 */

package demo03_pass_arg;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        var thFoo = new Thread(() -> doTask(1, 2, "red"));
        var thBar = new Thread(() -> doTask(3, 4, "blue"));

        thFoo.start();
        thBar.start();
    }


    private static void doTask(int a, double b, String c) {
        System.out.printf("%d  %.1f  %s %n", a, b, c);
    }

}
