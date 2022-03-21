/*
 * THE DATA SERVER PROBLEM
 * Version D: Solving the problem using a blocking queue
 */

package exer07_data_server;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;



public class AppD {

    public static void main(String[] args) throws InterruptedException {
        var server = new DataServer();
        server.processRequest();
    }


    private static class DataServer {
        public void processRequest() throws InterruptedException {
            final var lstFileName = new String[] { "foo.html", "bar.json" };
            final var queue = new LinkedBlockingQueue<String>();

            // The server checks auth user while reading files, concurrently
            new Thread(() -> processFiles(lstFileName, queue)).start();
            checkAuthUser();

            // The server waits for completion of loading files
            for (int i = lstFileName.length; i > 0; --i) {
                queue.take();
            }

            System.out.println("\nNow user is authorized and files are loaded");
            System.out.println("Do other tasks...\n");
        }


        // This task consumes CPU (and network bandwidth, maybe)
        private void checkAuthUser() {
            System.out.println("[   Auth   ] Start");
            // Send request to authenticator, check permissions, encrypt, decrypt...
            sleepNoEx(20);
            System.out.println("[   Auth   ] Done");
        }


        // This task consumes disk
        private void processFiles(String[] lstFileName, BlockingQueue<String> queue) {
            for (var fileName : lstFileName) {
                // Read file
                System.out.println("[ ReadFile ] Start " + fileName);
                sleepNoEx(10);
                System.out.println("[ ReadFile ] Done  " + fileName);

                try {
                    queue.put(fileName); // You may put file data here
                }
                catch (InterruptedException e) {
                }

                // Write log into disk
                sleepNoEx(5);
                System.out.println("[ WriteLog ]");
            }
        }


        private static void sleepNoEx(long seconds) {
            try { Thread.sleep(1000 * seconds); }
            catch (InterruptedException e) { }
        }
    }

}
