/*
 * READ-WRITE LOCKS
 */

package demo19_read_write_lock;

import java.util.Random;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.stream.IntStream;
import java.util.stream.Stream;



public class App {

    public static void main(String[] args) {
        ReadWriteLock rwlock = new ReentrantReadWriteLock();


        final int NUM_THREADS_READ = 10;
        final int NUM_THREADS_WRITE = 4;
        final int NUM_ARGS = 3;


        var lstArg = IntStream.range(0, NUM_ARGS).toArray();
        var rand = new Random();


        var lstThRead = Stream.generate(() -> new Thread(() -> {

            int waitTime = lstArg[ rand.nextInt(lstArg.length) ];
            try { Thread.sleep(1000 * waitTime);} catch (InterruptedException e) { }

            rwlock.readLock().lock();

            System.out.println("read: " + Resource.value);

            rwlock.readLock().unlock(); // Should be protected by try...finally...

        })).limit(NUM_THREADS_READ).toList();


        var lstThWrite = Stream.generate(() -> new Thread(() -> {

            int waitTime = lstArg[ rand.nextInt(lstArg.length) ];
            try { Thread.sleep(1000 * waitTime);} catch (InterruptedException e) { }

            rwlock.writeLock().lock();

            Resource.value = rand.nextInt(100);
            System.out.println("write: " + Resource.value);

            rwlock.writeLock().unlock(); // Should be protected by try...finally...

        })).limit(NUM_THREADS_WRITE).toList();


        lstThRead.forEach(Thread::start);
        lstThWrite.forEach(Thread::start);
    }

}



class Resource {
    public static volatile int value;
}
