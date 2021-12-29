﻿/*
 * BARRIERS
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo18A : IRunnable
{
    public void run()
    {
        var syncPoint = new Barrier(participantCount: 3);

        var lstArgs = new List<ThreadArg>
        {
            new ThreadArg{ userName = "foo", timeWait = 1 },
            new ThreadArg{ userName = "bar", timeWait = 2 },
            new ThreadArg{ userName = "ham", timeWait = 3 }
        };


        lstArgs.ForEach(arg => new Thread(() =>
        {

            Thread.Sleep(1000 * arg.timeWait);

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
        public int timeWait;
    }
}