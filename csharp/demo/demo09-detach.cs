/*
 * THREAD DETACHING
 */
using System;
using System.Threading;



class Demo09 : IRunnable
{
    public void run()
    {
        var thFoo = new Thread(() => {
            Console.WriteLine("foo is starting...");
            Thread.Sleep(2000);
            Console.WriteLine("foo is exiting...");
        });


        thFoo.IsBackground = true;
        thFoo.Start();


        // If I comment this statement,
        // thFoo will be forced into terminating with main thread
        Thread.Sleep(3000);


        Console.WriteLine("Main thread is exiting");
    }
}
