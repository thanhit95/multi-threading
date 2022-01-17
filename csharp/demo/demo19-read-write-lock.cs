/*
 * READ-WRITE LOCKS
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;



class Demo19 : IRunnable
{
    public void run()
    {
        var rwlk = new ReaderWriterLock();


        const int NUM_THREADS_READ = 10;
        const int NUM_THREADS_WRITE = 4;
        const int NUM_ARGS = 3;


        var arg = Enumerable.Range(0, NUM_ARGS).ToArray();
        var rand = new Random();

        var lstThRead = new List<Thread>();
        var lstThWrite = new List<Thread>();


        for (int i = 0; i < NUM_THREADS_READ; ++i)
        {
            lstThRead.Add(new Thread(() =>
            {
                int timeWait = arg[ rand.Next(arg.Length) ];
                Thread.Sleep(1000 * timeWait);

                // Should catch exception
                rwlk.AcquireReaderLock(1000);

                Console.WriteLine("read: " + Resource.value);

                rwlk.ReleaseReaderLock();
            }));
        }


        for (int i = 0; i < NUM_THREADS_WRITE; ++i)
        {
            lstThWrite.Add(new Thread(() =>
            {
                int timeWait = arg[ rand.Next(arg.Length) ];
                Thread.Sleep(1000 * timeWait);

                // Should catch exception
                rwlk.AcquireWriterLock(1000);

                Resource.value = rand.Next(100);
                Console.WriteLine("write: " + Resource.value);

                rwlk.ReleaseWriterLock();
            }));
        }


        lstThRead.ForEach(th => th.Start());
        lstThWrite.ForEach(th => th.Start());
    }



    class Resource
    {
        public static volatile int value;
    }
}
