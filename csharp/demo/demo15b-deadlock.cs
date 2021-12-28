/*
 * DEADLOCK
 * Version B
 */
using System;
using System.Threading;



class Demo15B : IRunnable
{
    private object resourceA = "resourceA";
    private object resourceB = "resourceB";


    public void run()
    {
        var foo = new Thread(() =>
        {
            lock (resourceA)
            {
                Console.WriteLine("foo entered resource A");
                Thread.Sleep(1000);

                lock (resourceB)
                {
                    Console.WriteLine("foo entered resource B");
                }
            }
        });


        var bar = new Thread(() =>
        {
            lock (resourceB)
            {
                Console.WriteLine("bar entered resource B");
                Thread.Sleep(1000);

                lock (resourceA)
                {
                    Console.WriteLine("bar entered resource A");
                }
            }
        });


        foo.Start();
        bar.Start();
        foo.Join();
        bar.Join();


        Console.WriteLine("You will never see this statement due to deadlock!");
    }
}
