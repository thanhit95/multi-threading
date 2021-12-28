/*
 * THREAD JOINS
 */
using System;
using System.Threading;



class Demo02B : IRunnable
{
    public void run()
    {
        Thread foo = new Thread(() => Console.WriteLine("foo"));
        Thread bar = new Thread(() => Console.WriteLine("bar"));

        foo.Start();
        bar.Start();

        //foo.Join();
        //bar.Join();

        /*
         * We do not need to call foo.Join() and bar.Join().
         * The reason is main thread will wait for the completion of all threads before app exits.
         */
    }
}
