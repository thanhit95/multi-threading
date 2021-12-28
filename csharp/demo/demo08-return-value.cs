/*
 * GETTING RETURNED VALUES FROM THREADS
 */
using System;
using System.Threading;



class Demo08 : IRunnable
{
    public void run()
    {
        int[] result = new int[2];

        var thFoo = new Thread(() => result[0] = doubleValue(5));
        var thBar = new Thread(() => result[1] = doubleValue(80));

        thFoo.Start();
        thBar.Start();

        // Wait until thFoo and thBar finish
        thFoo.Join();
        thBar.Join();

        Console.WriteLine(result[0]);
        Console.WriteLine(result[1]);
    }


    private int doubleValue(int value)
    {
        return value * 2;
    }
}
