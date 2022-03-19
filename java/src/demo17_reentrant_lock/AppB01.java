/*
 * REENTRANT LOCKS (RECURSIVE MUTEXES)
 * Version B01: A simple example
 *
 * Looking into the lock behind the "synchronized" keyword.
 * The lock behind the synchronized methods and blocks is reentrant lock.
 * That is, the current thread can acquire the same synchronized lock over and over again while holding it.
 */

package demo17_reentrant_lock;



public class AppB01 {

    public static void main(String[] args) {
        final Object resource = "resource";


        new Thread(() -> {
            synchronized (resource) {
                System.out.println("First time acquiring the resource");

                synchronized (resource) {
                    System.out.println("Second time acquiring the resource");
                }
            }
        }).start();
    }

}
