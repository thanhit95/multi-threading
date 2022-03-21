/*
 * THE DATA SERVER PROBLEM
 * Version C: Solving the problem using a count-down latch
 */
using System;
using System.Threading;



class Exer07C : IRunnable
{
    public void run()
    {
        var server = new DataServer();
        server.processRequest();
    }


    private class DataServer
    {
        public void processRequest()
        {
            var lstFileName = new String[] { "foo.html", "bar.json" };
            var readFileLatch = new CountdownEvent(lstFileName.Length);

            // The server checks auth user while reading files, concurrently
            new Thread(() => processFiles(lstFileName, readFileLatch)).Start();
            checkAuthUser();

            // The server waits for completion of loading files
            readFileLatch.Wait();

            Console.WriteLine("\nNow user is authorized and files are loaded");
            Console.WriteLine("Do other tasks...\n");
        }


        // This task consumes CPU (and network bandwidth, maybe)
        private void checkAuthUser()
        {
            Console.WriteLine("[   Auth   ] Start");
            // Send request to authenticator, check permissions, encrypt, decrypt...
            Thread.Sleep(20000);
            Console.WriteLine("[   Auth   ] Done");
        }


        // This task consumes disk
        private void processFiles(String[] lstFileName, CountdownEvent latch)
        {
            foreach (var fileName in lstFileName)
            {
                // Read file
                Console.WriteLine("[ ReadFile ] Start " + fileName);
                Thread.Sleep(10000);
                Console.WriteLine("[ ReadFile ] Done  " + fileName);

                latch.Signal();

                // Write log into disk
                Thread.Sleep(5000);
                Console.WriteLine("[ WriteLog ]");
            }
        }
    }
}
