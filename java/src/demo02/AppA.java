/*
 * THREAD JOINS
 */

package demo02;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        Thread th = new Thread(() -> System.out.println("First"));

        th.start();
        th.join();

        System.out.println("Second");
    }

}
