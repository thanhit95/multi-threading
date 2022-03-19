/*
 * THE READERS-WRITERS PROBLEM
 * Solution for the third readers-writers problem
 */

package exer03_readers_writers;

import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.stream.IntStream;



public class AppB {

    public static void main(String[] args) {
        final int NUM_READERS = 8;
        final int NUM_WRITERS = 6;


        var rand = new Random();


        var lstThReader = IntStream.range(0, NUM_READERS).mapToObj(i -> new Thread(() -> {
            try {
                doTaskReader(rand.nextInt(3));
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }));


        var lstThWriter = IntStream.range(0, NUM_WRITERS).mapToObj(i -> new Thread(() -> {
            try {
                doTaskWriter(rand.nextInt(3));
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }));


        lstThReader.forEach(Thread::start);
        lstThWriter.forEach(Thread::start);
    }


    private static void doTaskWriter(int timeDelay) throws InterruptedException {
        var rand = new Random();
        Thread.sleep(1000 * timeDelay);

        synchronized (Global.mutServiceQueue) {
            Global.mutResource.acquire();
        }

        Global.resource = rand.nextInt(100);
        System.out.println("Write " + Global.resource);

        Global.mutResource.release();
    }


    private static void doTaskReader(int timeDelay) throws InterruptedException {
        Thread.sleep(1000 * timeDelay);

        synchronized (Global.mutServiceQueue) {
            // Increase reader count
            synchronized (Global.mutReaderCount) {
                Global.readerCount += 1;

                if (1 == Global.readerCount)
                    Global.mutResource.acquire();
            }
        }

        // Do the reading
        int data = Global.resource;
        System.out.println("Read " + data);

        // Decrease reader count
        synchronized (Global.mutReaderCount) {
            Global.readerCount -= 1;

            if (0 == Global.readerCount)
                Global.mutResource.release();
        }
    }



    private static class Global {
        public static final Object mutServiceQueue = new Object();

        public static final Semaphore mutResource = new Semaphore(1);
        public static final Object mutReaderCount = new Object();

        public static volatile int resource = 0;
        public static int readerCount = 0;
    }

}
