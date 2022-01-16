/*
 * REENTRANT LOCKS (RECURSIVE MUTEXES)
 * Version A: A slightly hard example
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo17B : IRunnable
{
    public void run()
    {
        const int NUM_THREADS = 3;
        var lstWk = new List<Worker>();

        for (int i = 0; i < NUM_THREADS; ++i)
        {
            lstWk.Add(new Worker((char)(i + 'A')));
        }

        lstWk.ForEach(wk => wk.start());
    }



    class Worker
    {
        private static object lk = new object();

        private Thread th;
        private char name;

        public Worker(char name)
        {
            this.name = name;
            this.th = new Thread(doTask);
        }

        private void doTask()
        {
            Thread.Sleep(1000);

            lock (lk)
            {
                Console.WriteLine($"First time {name} acquiring the lock");

                lock (lk)
                {
                    Console.WriteLine($"Second time {name} acquiring the lock");
                }
            }
        }

        public void start()
        {
            th.Start();
        }
    }
}
