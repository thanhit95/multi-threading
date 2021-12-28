/*
 * THREAD DETACHING
 */
using System;
using System.Threading;



class Demo09 : IRunnable
{
    public void run()
    {
        var th = new Thread(() => {
            Console.WriteLine("Routine is starting...");
            Thread.Sleep(2000);
            Console.WriteLine("Routine is exiting...");
        });


        th.IsBackground = true;
        th.Start();


        // If I comment this statement,
        // the thread routine will be forced into terminating with main thread
        Thread.Sleep(3000);


        Console.WriteLine("Program is terminating");
    }
}
