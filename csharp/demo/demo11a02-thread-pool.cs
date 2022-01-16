/*
 * THREAD POOLS
 * Version A02: Passing arguments
 */
using System;
using System.Threading;



class Demo11A02 : IRunnable
{
    public void run()
    {
        WaitCallback wcb = (arg) =>
        {
            Console.WriteLine("Hello Multithreading " + arg);
        };


        ThreadPool.QueueUserWorkItem(
            arg => Console.WriteLine("Hello World " + arg),
            1
        );
        ThreadPool.QueueUserWorkItem(wcb, 2);
        ThreadPool.QueueUserWorkItem(doTask, 3);


        // Wait one second for task completion
        Thread.Sleep(1000);
    }


    private void doTask(object arg)
    {
        Console.WriteLine("Hello Thread Pool " + arg);
    }
}
