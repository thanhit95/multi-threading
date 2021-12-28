/*
 * MUTEXES
 *
 * Lock with a nonblocking mutex
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo13B : IRunnable
{
    private Mutex mut;
    private int counter;


    public void run()
    {
        const int NUM_THREADS = 50;

        mut = new Mutex();
        counter = 0;

        var lstTh = new List<Thread>();

        for (int i = 0; i < NUM_THREADS; ++i)
        {
            lstTh.Add(new Thread(routineCounter));
        }

        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());

        mut.Dispose();

        Console.WriteLine("counter = " + counter);
    }


    private void routineCounter()
    {
        Thread.Sleep(1000);

        if (false == mut.WaitOne(1))
        {
            return;
        }

        for (int i = 0; i < 10000; ++i)
            ++counter;

        mut.ReleaseMutex();
    }
}
