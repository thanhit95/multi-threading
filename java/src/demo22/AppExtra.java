/*
 * BLOCKING QUEUES
 * VersionC: Introduction to SynchronousQueue
 *
 * The SynchronousQueue is simply the BlockingQueue with capacity = 0.
 * Therefore, each insert operation must wait for a corresponding remove operation by another thread,
 *            and vice versa.
 */

package demo22;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.SynchronousQueue;



public class AppExtra {

    public static void main(String[] args) {
        final BlockingQueue<String> queue = new SynchronousQueue<>();
        new Thread(() -> producer(queue)).start();
        new Thread(() -> consumer(queue)).start();
    }


    private static void producer(BlockingQueue<String> queue) {
        try {
            queue.put("lorem");
            queue.put("ipsum");
            queue.put("fooooooo");
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    private static void consumer(BlockingQueue<String> queue) {
        String data = "";

        try {
            Thread.sleep(2000);

            for (int i = 0; i < 3; ++i) {
                System.out.println("\nWaiting for data...");

                data = queue.take();

                System.out.println("    " + data);
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
