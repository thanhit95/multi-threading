/*
 * DATA RACES
 * Version 02: Multithreading
 */
using System;
using System.Threading;
using System.Linq;



class Demo12B02 : IRunnable
{
    public void run()
    {
        const int N = 8;
        var a = Enumerable.Repeat(false, N + 1).ToArray();


        var thDiv2 = new Thread(() =>
        {
            for (int i = 2; i <= N; i += 2)
                a[i] = true;
        });

        var thDiv3 = new Thread(() =>
        {
            for (int i = 3; i <= N; i += 3)
                a[i] = true;
        });


        thDiv2.Start();
        thDiv3.Start();
        thDiv2.Join();
        thDiv3.Join();


        int result = a.Count(val => val);
        Console.WriteLine("Numbers of integers that are divisible by 2 or 3 is: " + result);
    }
}
