/*
 * EXECUTOR SERVICES AND THREAD POOLS
 * Version A01: System.Threading.ThreadPool
 *              Introduction
 */
using System;
using System.Threading;



class Demo11A01 : IRunnable
{
    public void run()
    {
        WaitCallback wcb = (arg) =>
        {
            Console.WriteLine("Hello Multithreading");
        };


        ThreadPool.QueueUserWorkItem(wcb);
        ThreadPool.QueueUserWorkItem(doTask);
        ThreadPool.QueueUserWorkItem(arg => Console.WriteLine("Hello World"));


        // Wait one second for task completion
        Thread.Sleep(1000);
    }


    private void doTask(object arg)
    {
        Console.WriteLine("Hello the Executor Service");
    }
}
