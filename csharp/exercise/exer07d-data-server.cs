/*
 * THE DATA SERVER PROBLEM
 * Version D: Solving the problem using a blocking queue
 */
using System;
using System.Collections.Concurrent;
using System.Threading;



class Exer07D : IRunnable
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
            var queue = new BlockingCollection<string>();

            // The server checks auth user while reading files, concurrently
            new Thread(() => processFiles(lstFileName, queue)).Start();
            checkAuthUser();

            // The server waits for completion of loading files
            for (int i = lstFileName.Length; i > 0; --i)
            {
                queue.Take();
            }

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
        private void processFiles(String[] lstFileName, BlockingCollection<string> queue)
        {
            foreach (var fileName in lstFileName)
            {
                // Read file
                Console.WriteLine("[ ReadFile ] Start " + fileName);
                Thread.Sleep(10000);
                Console.WriteLine("[ ReadFile ] Done  " + fileName);

                queue.Add(fileName); // You may put file data here

                // Write log into disk
                Thread.Sleep(5000);
                Console.WriteLine("[ WriteLog ]");
            }
        }
    }
}
