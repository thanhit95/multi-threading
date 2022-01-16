/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version B02: Using lambdas
 */
using System;
using System.Threading;



class Demo01B02 : IRunnable
{
    public void run()
    {
        Thread th = new Thread(() => Console.WriteLine("Hello from example thread"));

        th.Start();

        Console.WriteLine("Hello from main thread");
    }
}
