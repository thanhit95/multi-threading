/*
 * THREAD POOLS
 * Version B01: System.Threading.Tasks.Parallel
 *              Introduction
 */
using System;
using System.Threading.Tasks;



class Demo11B01 : IRunnable
{
    public void run()
    {
        Action<int> action = arg =>
        {
            Console.WriteLine($"Hello Multithreading {arg}");
        };


        Parallel.For(0, 4, action);
        // Main thread shall pause until all threads are completed

        Parallel.For(4, 8, doTask);
        // Main thread shall pause until all threads are completed

        Parallel.For(8, 12, i => Console.WriteLine($"Hello World {i}"));
        // Main thread shall pause until all threads are completed
    }


    private void doTask(int arg)
    {
        Console.WriteLine($"Hello Thread Pool {arg}");
    }
}
