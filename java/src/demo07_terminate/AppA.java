/*
 * FORCING A THREAD TO TERMINATE (i.e. killing the thread)
 * Version A: Interrupting the thread
 */

package demo07_terminate;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread(() -> {
            while (true) {
                System.out.println("Running...");

                try { Thread.sleep(1000); }
                catch (InterruptedException e) {
                    // Received interrupt signal, now current thread is going to exit
                    return;
                }
            }
        });


        th.start();

        Thread.sleep(3000);

        th.interrupt();
    }

}
