/*
 * SLEEP
 */
using System;
using System.Threading;



class Demo04 : IRunnable
{
    public void run()
    {
        var thFoo = new Thread(() =>
        {
            Console.WriteLine("foo is sleeping");
            Thread.Sleep(3000);
            Console.WriteLine("foo wakes up");
        });

        thFoo.Start();
        thFoo.Join();

        Console.WriteLine("Good bye");
    }
}
