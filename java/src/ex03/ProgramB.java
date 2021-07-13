/*
 * THE READERS-WRITERS PROBLEM
 * Solution for the third readers-writers problem
*/

package ex03;

import java.util.Random;
import java.util.concurrent.Semaphore;
import java.util.stream.IntStream;



public class ProgramB {

    public static void main(String[] args) {
        final int NUM_READERS = 8;
        final int NUM_WRITERS = 6;


        var rand = new Random();


        var lstThReader = IntStream.range(0, NUM_READERS).mapToObj(i -> new Thread(() -> {
            try {
                funcReader(rand.nextInt(3));
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }));


        var lstThWriter = IntStream.range(0, NUM_WRITERS).mapToObj(i -> new Thread(() -> {
            try {
                funcWriter(rand.nextInt(3));
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }));


        lstThReader.forEach(Thread::start);
        lstThWriter.forEach(Thread::start);
    }


    private static void funcWriter(int timeDelay) throws InterruptedException {
        var rand = new Random();
        Thread.sleep(1000 * timeDelay);

        Global.mutServiceQueue.acquire();

        Global.mutResource.acquire();

        Global.mutServiceQueue.release();

        Global.resource = rand.nextInt(100);
        System.out.println("Write " + Global.resource);

        Global.mutResource.release();
    }


    private static void funcReader(int timeDelay) throws InterruptedException {
        Thread.sleep(1000 * timeDelay);


        Global.mutServiceQueue.acquire();


        // Increase reader count
        synchronized (Global.mutReaderCount) {
            Global.readerCount += 1;

            if (1 == Global.readerCount)
                Global.mutResource.acquire();
        }


        Global.mutServiceQueue.release();


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



    class Global {
        static Semaphore mutServiceQueue = new Semaphore(1);

        static Semaphore mutResource = new Semaphore(1);
        static Object mutReaderCount = new Object();

        static volatile int resource = 0;
        static int readerCount = 0;
    }

}
