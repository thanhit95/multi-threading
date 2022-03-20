/*
 * BARRIERS AND LATCHES
 * Version B: Count-down latches
 *
 * Main thread waits for 3 child threads to get enough data to progress.
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo18B02 : IRunnable
{
    public void run()
    {
        var lstArg = new List<ThreadArg>
        {
            new ThreadArg{ message = "Send request to egg.net to get data", waitTime = 6 },
            new ThreadArg{ message = "Send request to foo.org to get data", waitTime = 2 },
            new ThreadArg{ message = "Send request to bar.com to get data", waitTime = 4 }
        };


        var syncPoint = new CountdownEvent(lstArg.Count);


        lstArg.ForEach(arg => new Thread(() =>
        {

            Thread.Sleep(1000 * arg.waitTime);

            Console.WriteLine(arg.message);
            syncPoint.Signal();

            Thread.Sleep(8000);
            Console.WriteLine("Cleanup");

        }).Start());


        syncPoint.Wait();
        Console.WriteLine("\nNow we have enough data to progress to next step\n");
    }



    class ThreadArg
    {
        public string message;
        public int waitTime;
    }
}
