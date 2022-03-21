/*
 * THE DATA SERVER PROBLEM
 * Version A: Solving the problem using a condition variable
 */
using System;
using System.Threading;



class Exer07A : IRunnable
{
    public void run()
    {
        var server = new DataServer();
        server.processRequest();
    }


    private class DataServer
    {
        private class Counter
        {
            public int value;
            public Counter(int value)
            {
                this.value = value;
            }
        }


        public void processRequest()
        {
            var lstFileName = new String[] { "foo.html", "bar.json" };
            var counter = new Counter(lstFileName.Length);

            // The server checks auth user while reading files, concurrently
            new Thread(() => processFiles(lstFileName, counter)).Start();
            checkAuthUser();

            // The server waits for completion of loading files
            lock (counter)
            {
                while (counter.value > 0)
                {
                    Monitor.Wait(counter, 10000); // timeout = 10 seconds
                }
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
        private void processFiles(String[] lstFileName, Counter counter)
        {
            foreach (var fileName in lstFileName)
            {
                // Read file
                Console.WriteLine("[ ReadFile ] Start " + fileName);
                Thread.Sleep(10000);
                Console.WriteLine("[ ReadFile ] Done  " + fileName);

                lock (counter)
                {
                    --counter.value;
                    Monitor.Pulse(counter);
                }

                // Write log into disk
                Thread.Sleep(5000);
                Console.WriteLine("[ WriteLog ]");
            }
        }
    }
}
