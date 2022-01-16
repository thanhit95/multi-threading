/*
 * THREAD JOINS
 */
using System;
using System.Threading;



class Demo02B : IRunnable
{
    public void run()
    {
        Thread thFoo = new Thread(() => Console.WriteLine("foo"));
        Thread thBar = new Thread(() => Console.WriteLine("bar"));

        thFoo.Start();
        thBar.Start();

        // thFoo.Join();
        // thBar.Join();

        /*
         * We do not need to call thFoo.Join() and thBar.Join().
         * The reason is main thread will wait for the completion of all threads before app exits.
         */
    }
}
