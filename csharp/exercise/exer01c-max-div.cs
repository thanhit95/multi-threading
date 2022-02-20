/*
 * MAXIMUM NUMBER OF DIVISORS
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer01C : IRunnable
{
    public void run()
    {
        const int RANGE_START = 1;
        const int RANGE_STOP = 100000;
        const int NUM_THREADS = 8;

        var lstWorkerArg = prepareArg(RANGE_START, RANGE_STOP, NUM_THREADS);
        var lstTh = new List<Thread>();
        var finalRes = new WorkerResult();


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

                finalRes.update(resValue, resNumDiv);
            }));
        }


        var tpStart = DateTime.Now;

        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());

        var timeElapsed = (DateTime.Now - tpStart).TotalSeconds;

        Console.WriteLine("The integer which has largest number of divisors is " + finalRes.value);
        Console.WriteLine("The largest number of divisor is " + finalRes.numDiv);
        Console.WriteLine("Time elapsed = " + timeElapsed);
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


    class WorkerResult
    {
        public int value = 0;
        public int numDiv = 0;

        public void update(int value, int numDiv)
        {
            lock (this)
            {
                if (this.numDiv < numDiv)
                {
                    this.numDiv = numDiv;
                    this.value = value;
                }
            }
        }
    }
}
