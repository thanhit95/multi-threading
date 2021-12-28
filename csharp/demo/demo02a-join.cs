/*
 * THREAD JOINS
 */
using System;
using System.Threading;



class Demo02A : IRunnable
{
    public void run()
    {
        Thread th = new Thread(() => Console.WriteLine("First"));

        th.Start();
        th.Join();

        Console.WriteLine("Second");
    }
}
