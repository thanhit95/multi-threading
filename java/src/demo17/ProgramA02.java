/*
 * REENTRANT LOCK (RECURSIVE MUTEX)
 * Version A02: Slightly hard example
 */

package demo17;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.IntStream;



public class ProgramA02 {

    public static void main(String[] args) {
        final int NUM_THREADS = 3;

        IntStream.range(0, NUM_THREADS).forEach(i -> new MyTaskA((char)(i + 'A')).start());
    }

}



class MyTaskA extends Thread {
    private static Lock lk = new ReentrantLock();


    private char name;


    public MyTaskA(char name) {
        this.name = name;
    }


    @Override
    public void run() {
        try { Thread.sleep(1000); } catch (InterruptedException e) { }

        lk.lock();
        System.out.println("First time %c acquiring the lock".formatted(name));

        lk.lock();
        System.out.println("Second time %c acquiring the lock".formatted(name));

        lk.unlock();
        lk.unlock();
    }
}
