/*
 * BARRIERS AND LATCHES
 * Version A: Barriers
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo18A03 : IRunnable
{
    public void run()
    {
        var syncPointA = new Barrier(participantCount: 2);
        var syncPointB = new Barrier(participantCount: 2);


        var lstArg = new List<ThreadArg>
        {
            new ThreadArg{ userName = "lorem", waitTime = 1 },
            new ThreadArg{ userName = "ipsum", waitTime = 3 }
        };


        lstArg.ForEach(arg => new Thread(() =>
        {

            Thread.Sleep(1000 * arg.waitTime);

            Console.WriteLine("Get request from " + arg.userName);
            syncPointA.SignalAndWait();

            Thread.Sleep(4000);

            Console.WriteLine("Process request for " + arg.userName);
            syncPointB.SignalAndWait();

            Console.WriteLine("Done " + arg.userName);

        }).Start());
    }



    class ThreadArg
    {
        public string userName;
        public int waitTime;
    }
}
