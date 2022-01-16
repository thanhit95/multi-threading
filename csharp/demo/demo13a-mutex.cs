/*
 * MUTEXES
 *
 * Without synchronization (by a mutex), we are not sure that result = 30000
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo13A : IRunnable
{
    private Mutex mut;
    private int counter;


    public void run()
    {
        const int NUM_THREADS = 3;

        mut = new Mutex();
        counter = 0;

        var lstTh = new List<Thread>();

        for (int i = 0; i < NUM_THREADS; ++i)
        {
            lstTh.Add(new Thread(doTask));
        }

        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());

        mut.Dispose();

        Console.WriteLine("counter = " + counter);
    }


    private void doTask()
    {
        Thread.Sleep(1000);

        mut.WaitOne();

        for (int i = 0; i < 10000; ++i)
            ++counter;

        mut.ReleaseMutex();
    }
}
