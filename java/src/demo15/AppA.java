/*
 * DEADLOCK
 * Version A
 */

package demo15;

import java.util.concurrent.Semaphore;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var mutex = new Semaphore(1);

        var foo = new Thread(() -> threadFunc(mutex, "foo"));
        var bar = new Thread(() -> threadFunc(mutex, "bar"));

        foo.start();
        bar.start();

        foo.join();
        bar.join();

        System.out.println("You will never see this statement due to deadlock!");
    }


    private static void threadFunc(Semaphore mutex, String name) {
        try {
            mutex.acquire();
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println(name + " acquired resource");

        // mutex.release(); // forget this statement ==> deadlock
    }

}
