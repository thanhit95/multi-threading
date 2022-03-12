/*
 * EXECUTOR SERVICES AND THREAD POOLS
 * Version A04: System.Threading.ThreadPool
 *              Waiting for task completion by AutoResetEvent
 */
using System;
using System.Threading;



class Demo11A04 : IRunnable
{
    public void run()
    {
        // INIT
        const int N = 5;

        var lstResult = new int[N];
        var lstEvent = new AutoResetEvent[N];

        for (int i = 0; i < N; ++i)
            lstEvent[i] = new AutoResetEvent(false);


        // RUN
        for (int i = 0; i < N; ++i)
        {
            int ith = i;

            ThreadPool.QueueUserWorkItem(_ =>
                {
                    lstResult[ith] = ith * ith;
                    lstEvent[ith].Set();
                }
            );
        }


        WaitHandle.WaitAll(lstEvent);


        // PRINT RESULTS
        Array.ForEach(lstResult, res => Console.WriteLine(res));
    }
}
