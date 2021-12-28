/*
 * THREAD-LOCAL STORAGE
 * Avoiding synchronization using Thread-Local Storage
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo23B : IRunnable
{
    public void run()
    {
        const int NUM_THREADS = 3;
        var lstTh = new List<Thread>();

        for (int i = 0; i < NUM_THREADS; ++i)
        {
            int t = i;

            lstTh.Add(new Thread(() =>
            {
                Thread.Sleep(1000);

                for (int i = 0; i < 1000; ++i)
                    MyTask.increaseCounter();

                Console.WriteLine($"Thread {t} gives counter = {MyTask.getCounter()}");
            }));
        }

        lstTh.ForEach(th => th.Start());

        /*
         * By using thread-local storage, each thread has its own counter.
         * So, the counter in one thread is completely independent of each other.
         *
         * Thread-local storage helps us to AVOID SYNCHRONIZATION.
         */
    }


    class Counter
    {
        public int value = 0;
    }


    class MyTask
    {
        private static ThreadLocal<Counter> thlCounter = new ThreadLocal<Counter>(() => new Counter());

        public static int getCounter()
        {
            return thlCounter.Value.value;
        }

        public static void increaseCounter()
        {
            var counter = thlCounter.Value;
            ++counter.value;
        }
    }
}
