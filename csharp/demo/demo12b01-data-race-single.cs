/*
 * DATA RACES
 * Version 01: Without multithreading
 */
using System;
using System.Threading;
using System.Linq;



class Demo12B01 : IRunnable
{
    public void run()
    {
        const int N = 8;
        int result = getResult(N);
        Console.WriteLine("Numbers of integers that are divisible by 2 or 3 is: " + result);
    }


    private int getResult(int N)
    {
        var a = Enumerable.Repeat(false, N + 1).ToArray();

        for (int i = 1; i <= N; ++i)
            if (i % 2 == 0 || i % 3 == 0)
                a[i] = true;

        // res = number of true values in array
        int res = a.Count(val => val);
        return res;
    }
}
