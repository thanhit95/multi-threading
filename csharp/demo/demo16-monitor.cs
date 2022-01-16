/*
 * MONITORS
 * Implementation of a monitor for managing a counter
 *
 * Notes:
 * - In C#, Monitor is already available (class System.Threading.Monitor).
 * - From a simple point of view in C#,
 *      "lock" keyword is shorthand for using System.Threading.Monitor + try/finally.
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo16 : IRunnable
{
    public void run()
    {
        var counter = new Counter();
        var monitor = new MyMonitor();
        monitor.init(counter);


        const int NUM_THREADS = 3;
        var lstTh = new List<Thread>();

        for (int i = 0; i < NUM_THREADS; ++i)
        {
            lstTh.Add(new Thread(() =>
            {
                Thread.Sleep(1000);

                for (int j = 0; j < 10000; ++j)
                    monitor.increaseCounter();
            }));
        }


        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());


        Console.WriteLine("counter = " + counter.value);
    }



    class Counter
    {
        public int value = 0;
    }



    class MyMonitor
    {
        private Counter counter = null;

        public void init(Counter counter)
        {
            this.counter = counter;
        }

        public void increaseCounter()
        {
            lock (counter)
            {
                ++counter.value;
            }
        }
    }
}
