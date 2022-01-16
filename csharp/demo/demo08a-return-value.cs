/*
 * GETTING RETURNED VALUES FROM THREADS
 */
using System;
using System.Threading;



class Demo08A : IRunnable
{
    public void run()
    {
        int resFoo = 0, resBar = 0;

        var thFoo = new Thread(() => resFoo = doubleValue(5));
        var thBar = new Thread(() => resBar = doubleValue(80));

        thFoo.Start();
        thBar.Start();

        // Wait until thFoo and thBar finish
        thFoo.Join();
        thBar.Join();

        Console.WriteLine(resFoo);
        Console.WriteLine(resBar);
    }


    private int doubleValue(int value)
    {
        return value * 2;
    }
}
