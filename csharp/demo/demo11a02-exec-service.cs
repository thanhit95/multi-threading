/*
 * EXECUTOR SERVICES AND THREAD POOLS
 * Version A02: System.Threading.ThreadPool
 *              Passing arguments
 */
using System;
using System.Threading;



class Demo11A02 : IRunnable
{
    public void run()
    {
        WaitCallback wcb = (arg) =>
        {
            Console.WriteLine($"Hello Multithreading {arg}");
        };


        ThreadPool.QueueUserWorkItem(wcb, 1);
        ThreadPool.QueueUserWorkItem(doTask, 2);

        ThreadPool.QueueUserWorkItem(
            arg => Console.WriteLine($"Hello World {arg}"),
            3
        );


        // Wait one second for task completion
        Thread.Sleep(1000);
    }


    private void doTask(object arg)
    {
        Console.WriteLine($"Hello the Executor Service {arg}");
    }
}
