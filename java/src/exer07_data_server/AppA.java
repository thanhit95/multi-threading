/*
 * THE DATA SERVER PROBLEM
 * Version A: Solving the problem using a condition variable
 */

package exer07_data_server;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        var server = new DataServer();
        server.processRequest();
    }


    private static class DataServer {
        private class Counter {
            public int value;
            public Counter(int value) {
                this.value = value;
            }
        }


        public void processRequest() throws InterruptedException {
            final var lstFileName = new String[] { "foo.html", "bar.json" };
            final var counter = new Counter(lstFileName.length);

            // The server checks auth user while reading files, concurrently
            new Thread(() -> processFiles(lstFileName, counter)).start();
            checkAuthUser();

            // The server waits for completion of loading files
            synchronized (counter) {
                while (counter.value > 0) {
                    counter.wait(10000); // timeout = 10 seconds
                }
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
        private void processFiles(String[] lstFileName, Counter counter) {
            for (var fileName : lstFileName) {
                // Read file
                System.out.println("[ ReadFile ] Start " + fileName);
                sleepNoEx(10);
                System.out.println("[ ReadFile ] Done  " + fileName);

                synchronized (counter) {
                    --counter.value;
                    counter.notify();
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
