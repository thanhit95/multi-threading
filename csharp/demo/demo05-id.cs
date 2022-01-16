/*
 * GETTING THREAD'S ID
 */
using System;
using System.Threading;



class Demo05 : IRunnable
{
    public void run()
    {
        ThreadStart doTask = () =>
        {
            int id = Thread.CurrentThread.ManagedThreadId;
            Console.WriteLine(id);
        };

        Thread thFoo = new Thread(doTask);
        Thread thBar = new Thread(doTask);

        Console.WriteLine("foo's id: " + thFoo.ManagedThreadId);
        Console.WriteLine("bar's id: " + thBar.ManagedThreadId);

        thFoo.Start();
        thBar.Start();
    }
}
