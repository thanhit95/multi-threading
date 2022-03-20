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
            new ThreadArg{ userName = "lorem", waitTime = 1 },
            new ThreadArg{ userName = "ipsum", waitTime = 2 },
            new ThreadArg{ userName = "dolor", waitTime = 3 }
        };


        lstArg.ForEach(arg => new Thread(() =>
        {

            Thread.Sleep(1000 * arg.waitTime);

            Console.WriteLine("Get request from " + arg.userName);

            syncPoint.Signal();
            syncPoint.Wait();

            Console.WriteLine("Done " + arg.userName);

        }).Start());
    }



    class ThreadArg
    {
        public string userName;
        public int waitTime;
    }
}
