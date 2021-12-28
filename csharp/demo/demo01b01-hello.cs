/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B01: Using lambdas with ThreadStart
 */
using System;
using System.Threading;



class Demo01B01 : IRunnable
{
    public void run()
    {
        ThreadStart threadFunc = new ThreadStart(() =>
        {
            Console.WriteLine("Hello from Lorem thread");
        });

        Thread th1 = new Thread(threadFunc);
        Thread th2 = new Thread(threadFunc);

        th1.Start();
        th2.Start();

        Console.WriteLine("Hello from main thread");
    }
}
