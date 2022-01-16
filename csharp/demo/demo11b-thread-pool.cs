/*
 * THREAD POOLS
 * Version B: Waiting for task completion by AutoResetEvent
 */
using System;
using System.Threading;



class Demo11B : IRunnable
{
    public void run()
    {
        const int N = 5;


        // INIT
        var inp = new int[N];
        var result = new int[N];
        var lstEvent = new AutoResetEvent[N];

        for (int i = 0; i < N; ++i)
        {
            inp[i] = i + 100;
            lstEvent[i] = new AutoResetEvent(false);
        }


        // RUN
        for (int i = 0; i < N; ++i)
        {
            int index = i;

            ThreadPool.QueueUserWorkItem(arg =>
                {
                    int iarg = (int)arg;
                    result[index] = iarg * 2;
                    lstEvent[index].Set();
                },
                inp[i]
            );
        }


        WaitHandle.WaitAll(lstEvent);


        // PRINT RESULTS
        for (int i = 0; i < N; ++i)
        {
            Console.WriteLine(result[i]);
        }
    }
}
