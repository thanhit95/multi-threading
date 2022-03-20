/*
 * BARRIERS AND LATCHES
 * Version A: Barriers
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo18A01 : IRunnable
{
    public void run()
    {
        var syncPoint = new Barrier(participantCount: 3);


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
            syncPoint.SignalAndWait();

            Console.WriteLine("Process request for " + arg.userName);
            syncPoint.SignalAndWait();

            Console.WriteLine("Done " + arg.userName);

        }).Start());
    }



    class ThreadArg
    {
        public string userName;
        public int waitTime;
    }
}
