/*
 * SYNCHRONIZED
 * Version D: Looking into the lock behind the "synchronized" keyword
 *
 * The lock behind the synchronized methods and blocks is reentrant lock.
 * That is, the current thread can acquire the same synchronized lock over and over again while holding it.
 */

package demo14;

import java.util.stream.IntStream;



public class ProgramD {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;


        var lstTh = IntStream.range(0, NUM_THREADS).mapToObj(i -> new MyTaskD((char)(i + 'A'))).toList();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();
    }

}



class MyTaskD extends Thread {
    private static Object lock = new Object();


    private char name;


    public MyTaskD(char name) {
        this.name = name;
    }


    @Override
    public void run() {
        try { Thread.sleep(1000); } catch (InterruptedException e) { }

        synchronized(lock) {
            System.out.println("First time %c acquiring the lock".formatted(name));

            synchronized (lock) {
                System.out.println("Second time %c acquiring the lock".formatted(name));
            }
        }
    }
}
