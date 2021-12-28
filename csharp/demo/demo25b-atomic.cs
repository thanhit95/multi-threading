/*
 * ATOMIC ACCESS
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo25B : IRunnable
{
    public void run()
    {
        ThreadStart routine = () =>
        {
            Thread.Sleep(1000);
            Interlocked.Increment(ref Global.counter);
        };


        var lstTh = new List<Thread>();

        for (int i = 0; i < 1000; ++i)
            lstTh.Add(new Thread(routine));


        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());


        // counter = 1000
        Console.WriteLine("counter = " + Global.counter);
    }


    class Global
    {
        public static volatile int counter = 0;
    }
}
