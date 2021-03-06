/*
 * FORCING A THREAD TO TERMINATE (i.e. killing the thread)
 * Version B: Using a flag to notify the thread
 *
 * Beside atomic variables, you can use the "volatile" specifier.
 */

package demo07_terminate;

import java.util.concurrent.atomic.AtomicBoolean;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        var flagStop = new AtomicBoolean(false);

        var th = new Thread(() -> {
            while (true) {
                if (flagStop.get())
                    break;

                System.out.println("Running...");

                try { Thread.sleep(1000); }
                catch (InterruptedException e) { }
            }
        });


        th.start();

        Thread.sleep(3000);

        flagStop.set(true);
    }

}
