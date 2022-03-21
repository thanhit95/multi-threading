/*
 * THE DATA SERVER PROBLEM
 * Version B: Solving the problem using a semaphore
 */

package exer07_data_server;

import java.util.concurrent.Semaphore;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        var server = new DataServer();
        server.processRequest();
    }


    private static class DataServer {
        public void processRequest() throws InterruptedException {
            final var lstFileName = new String[] { "foo.html", "bar.json" };
            final var sem = new Semaphore(0);

            // The server checks auth user while reading files, concurrently
            new Thread(() -> processFiles(lstFileName, sem)).start();
            checkAuthUser();

            // The server waits for completion of loading files
            for (int i = lstFileName.length; i > 0; --i) {
                sem.acquire();
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
        private void processFiles(String[] lstFileName, Semaphore sem) {
            for (var fileName : lstFileName) {
                // Read file
                System.out.println("[ ReadFile ] Start " + fileName);
                sleepNoEx(10);
                System.out.println("[ ReadFile ] Done  " + fileName);

                sem.release();

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
