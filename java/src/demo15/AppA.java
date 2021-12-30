/*
 * DEADLOCK
 * Version A
 */

package demo15;

import java.util.concurrent.Semaphore;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var mutex = new Semaphore(1);

        var thFoo = new Thread(() -> doTask(mutex, "foo"));
        var thBar = new Thread(() -> doTask(mutex, "bar"));

        thFoo.start();
        thBar.start();

        thFoo.join();
        thBar.join();

        System.out.println("You will never see this statement due to deadlock!");
    }


    private static void doTask(Semaphore mutex, String name) {
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
