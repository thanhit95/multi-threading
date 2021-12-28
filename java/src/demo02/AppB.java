/*
 * THREAD JOINS
 */

package demo02;



public class AppB {

    public static void main(String[] args) {
        Thread foo = new Thread(() -> System.out.println("foo"));
        Thread bar = new Thread(() -> System.out.println("bar"));

        foo.start();
        bar.start();

        // foo.join();
        // bar.join();

        /*
         * We do not need to call foo.join() and bar.join().
         * The reason is main thread will wait for the completion of all threads before app exits.
         */
    }

}
