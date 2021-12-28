/*
 * SLEEP
 */
using System;
using System.Threading;



class Demo04 : IRunnable
{
    public void run()
    {
        var th = new Thread(() =>
        {
            Thread.Sleep(2000);
            Console.WriteLine("Done!!!");
        });

        th.Start();

        Console.WriteLine("main thread is running...");
    }
}
