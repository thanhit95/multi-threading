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
        var thFoo = new Thread(() =>
        {
            lock (resourceA)
            {
                Console.WriteLine("foo acquired resource A");
                Thread.Sleep(1000);

                lock (resourceB)
                {
                    Console.WriteLine("foo acquired resource B");
                }
            }
        });


        var thBar = new Thread(() =>
        {
            lock (resourceB)
            {
                Console.WriteLine("bar acquired resource B");
                Thread.Sleep(1000);

                lock (resourceA)
                {
                    Console.WriteLine("bar acquired resource A");
                }
            }
        });


        thFoo.Start();
        thBar.Start();
        thFoo.Join();
        thBar.Join();


        Console.WriteLine("You will never see this statement due to deadlock!");
    }
}
