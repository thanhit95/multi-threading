/*
 * GETTING THREAD'S ID
 */
using System;
using System.Threading;



class Demo05 : IRunnable
{
    public void run()
    {
        ThreadStart routine = () =>
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            Console.WriteLine(id);
        };

        Thread foo = new Thread(routine);
        Thread bar = new Thread(routine);

        Console.WriteLine("foo's id is " + foo.ManagedThreadId);
        Console.WriteLine("bar's id is " + bar.ManagedThreadId);

        foo.Start();
        bar.Start();
    }
}
