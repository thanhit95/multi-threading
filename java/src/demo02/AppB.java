/*
 * THREAD JOINS
 */

package demo02;



public class AppB {

    public static void main(String[] args) {
        Thread thFoo = new Thread(() -> System.out.println("foo"));
        Thread thBar = new Thread(() -> System.out.println("bar"));

        thFoo.start();
        thBar.start();

        // thFoo.join();
        // thBar.join();

        /*
         * We do not need to call thFoo.join() and thBar.join().
         * The reason is main thread will wait for the completion of all threads before app exits.
         */
    }

}
