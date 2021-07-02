/*
 * REENTRANT LOCK (RECURSIVE MUTEX)
 * Version B: Complex example
*/

package demo17;

import java.util.stream.IntStream;



public class ProgramB {

    public static void main(String[] args) throws InterruptedException {
        final int NUM_THREADS = 3;

        IntStream.range(0, NUM_THREADS).forEach(i -> new MyTask((char)(i + 'A')).start());
    }

}



class MyTask extends Thread {
    private static Object lock = new Object();


    private char name;


    public MyTask(char name) {
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
