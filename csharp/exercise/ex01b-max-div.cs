/*
 * MAXIMUM NUMBER OF DIVISORS
 */
using System;
using System.Collections.Generic;
using System.Threading;
using System.Linq;



class Exer01B : IRunnable
{
    public void run()
    {
        const int RANGE_START = 1;
        const int RANGE_STOP = 100000;
        const int NUM_THREADS = 8;

        var lstWorkerArg = prepareArg(RANGE_START, RANGE_STOP, NUM_THREADS);
        var lstWorkerRes = new List<WorkerResult>();
        var lstTh = new List<Thread>();


        for (int ith = 0; ith < NUM_THREADS; ++ith)
        {
            var arg = lstWorkerArg[ith];

            lstTh.Add(new Thread(() =>
            {
                int resValue = 0;
                int resNumDiv = 0;

                for (int i = arg.iStart; i <= arg.iEnd; ++i)
                {
                    int numDiv = 0;

                    for (int j = i / 2; j > 0; --j)
                        if (i % j == 0)
                            ++numDiv;

                    if (resNumDiv < numDiv)
                    {
                        resNumDiv = numDiv;
                        resValue = i;
                    }
                }

                lock (lstWorkerRes)
                {
                    lstWorkerRes.Add(new WorkerResult(resValue, resNumDiv));
                }
            }));
        }


        var tpStart = DateTime.Now;

        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());
        var finalRes = lstWorkerRes.OrderByDescending(res => res.numDiv).First();

        var timeElapsed = (DateTime.Now - tpStart).TotalSeconds;

        Console.WriteLine("The integer which has largest number of divisors is " + finalRes.value);
        Console.WriteLine("The largest number of divisor is " + finalRes.numDiv);
        Console.WriteLine("Time elapsed = " + timeElapsed);


        /*
         * BETTER WAY (avoiding synchronization of lstWorkerRes):
         *
         * - Initialize lstWorkerRes with null objects.
         *   Of course, the number of objects is NUM_THREADS.
         *
         * - In thread function:
         *   lstWorkerRes[threadIndex] = new WorkerResult(resValue, resNumDiv);
         */
    }


    private List<WorkerArg> prepareArg(int rangeStart, int rangeEnd, int numThreads)
    {
        int rangeA, rangeB, rangeBlock;

        rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
        rangeA = rangeStart;

        var lstWorkerArg = new List<WorkerArg>();

        for (int i = 0; i < numThreads; ++i, rangeA += rangeBlock)
        {
            rangeB = rangeA + rangeBlock - 1;

            if (i == numThreads - 1)
                rangeB = rangeEnd;

            lstWorkerArg.Add(new WorkerArg(rangeA, rangeB));
        }

        return lstWorkerArg;
    }


    readonly struct WorkerArg
    {
        public readonly int iStart, iEnd;
        public WorkerArg(int iStart, int iEnd) => (this.iStart, this.iEnd) = (iStart, iEnd);
    }


    readonly struct WorkerResult
    {
        public readonly int value, numDiv;
        public WorkerResult(int value, int numDiv) => (this.value, this.numDiv) = (value, numDiv);
    }
}
