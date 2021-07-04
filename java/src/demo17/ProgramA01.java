/*
 * REENTRANT LOCK (RECURSIVE MUTEX)
 * Version A01: Simple example
 */

package demo17;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



public class ProgramA01 {

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
