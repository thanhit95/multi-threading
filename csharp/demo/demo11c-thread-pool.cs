/*
 * THREAD POOLS
 * Version C: Fixed thread pools
 */
using System;
using System.Threading;
using System.Threading.Tasks;



class Demo11C : IRunnable
{
    public void run()
    {
        const int N = 5;

        var prlOptions = new ParallelOptions { MaxDegreeOfParallelism = 2 };

        Parallel.For(0, N, prlOptions,
            i =>
            {
                char name = (char)(i + 'A');
                Console.WriteLine($"Task {name} is starting");
                Thread.Sleep(3000);
                Console.WriteLine($"Task {name} is completed");
            }
        );
    }
}
