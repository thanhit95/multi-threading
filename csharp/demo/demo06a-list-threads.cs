/*
 * LIST OF MULTIPLE THREADS
 * Version A: Using List
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo06A : IRunnable
{
    public void run()
    {
        const int NUM_THREADS = 5;
        var lstTh = new List<Thread>();


        for (int i = 0; i < NUM_THREADS; ++i)
        {
            /*
             * Due to the reference mechanism,
             * if you remove the line "int ith = i", the result will be wrong.
             */
            int ith = i;

            lstTh.Add(new Thread(() =>
            {
                Thread.Sleep(500);
                Console.WriteLine(ith);
            }));
        }


        lstTh.ForEach(th => th.Start());
        // foreach (var th in lstTh)
        // {
        //     th.Start();
        // }
    }
}
