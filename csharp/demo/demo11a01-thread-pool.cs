/*
 * THREAD POOLS
 * Version A01: Introduction
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


        ThreadPool.QueueUserWorkItem(arg => Console.WriteLine("Hello World"));
        ThreadPool.QueueUserWorkItem(wcb);
        ThreadPool.QueueUserWorkItem(doTask);


        // Wait one second for task completion
        Thread.Sleep(1000);
    }


    private void doTask(object arg)
    {
        Console.WriteLine("Hello Thread Pool");
    }
}
