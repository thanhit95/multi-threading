/*
 * THREAD POOLS
 * Version B02: System.Threading.Tasks.Parallel
 */
using System;
using System.Threading.Tasks;



class Demo11B02 : IRunnable
{
    public void run()
    {
        // EXAMPLE 1
        const int N = 5;
        var lstResult = new int[N];

        Parallel.For(0, N, i =>
        {
            lstResult[i] = i * i;
        });

        Array.ForEach(lstResult, res => Console.Write(res + "\t"));
        Console.WriteLine();


        // EXAMPLE 2
        var lstArg = new double[] { -3.14, -9.8, 0, 1, -6 };

        Parallel.ForEach(lstArg, arg =>
        {
            Console.Write(Math.Abs(arg) + "\t");
        });

        Console.WriteLine();
    }
}
