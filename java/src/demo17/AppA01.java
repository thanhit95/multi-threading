/*
 * REENTRANT LOCK (RECURSIVE MUTEX)
 * Version A01: A simple example
 */

package demo17;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



public class AppA01 {

    public static void main(String[] args) {
        Lock lk = new ReentrantLock();


        new Thread(() -> {

            lk.lock();
            System.out.println("First time acquiring the resource");

            lk.lock();
            System.out.println("Second time acquiring the resource");

            lk.unlock();
            lk.unlock();

        }).start();
    }

}
