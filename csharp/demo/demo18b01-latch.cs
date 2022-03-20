/*
 * BARRIERS AND LATCHES
 * Version B: Count-down latches
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo18B01 : IRunnable
{
    public void run()
    {
        var syncPoint = new CountdownEvent(3);


        var lstArg = new List<ThreadArg>
        {
            new ThreadArg{ userName = "lorem", timeWait = 1 },
            new ThreadArg{ userName = "ipsum", timeWait = 2 },
            new ThreadArg{ userName = "dolor", timeWait = 3 }
        };


        lstArg.ForEach(arg => new Thread(() =>
        {

            Thread.Sleep(1000 * arg.timeWait);

            Console.WriteLine("Get request from " + arg.userName);

            syncPoint.Signal();
            syncPoint.Wait();

            Console.WriteLine("Done " + arg.userName);

        }).Start());
    }



    class ThreadArg
    {
        public string userName;
        public int timeWait;
    }
}
