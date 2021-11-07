/*
 * DEADLOCK
 * Version A
 */

package demo14;

import java.util.concurrent.Semaphore;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var mutex = new Semaphore(1);

        var thFoo = new Thread(() -> routine(mutex, "foo"));
        var thBar = new Thread(() -> routine(mutex, "bar"));

        thFoo.start();
        thBar.start();

        thFoo.join();
        thBar.join();

        System.out.println("You will never see this statement due to deadlock!");
    }


    private static void routine(Semaphore mutex, String name) {
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
