/*
 * THREAD POOLS
 * Version A05: System.Threading.ThreadPool
 *              Waiting for task completion by CountdownEvent
 */
using System;
using System.Threading;



class Demo11A05 : IRunnable
{
    public void run()
    {
        // INIT
        const int N = 5;

        var lstResult = new int[N];
        var cde = new CountdownEvent(N);


        // RUN
        for (int i = 0; i < N; ++i)
        {
            int ith = i;

            ThreadPool.QueueUserWorkItem(_ =>
                {
                    lstResult[ith] = ith * ith;
                    cde.Signal();
                }
            );
        }


        cde.Wait();


        // PRINT RESULTS
        Array.ForEach(lstResult, res => Console.WriteLine(res));


        cde.Dispose();
    }
}
