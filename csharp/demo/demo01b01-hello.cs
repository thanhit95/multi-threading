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
        ThreadStart doTask = new ThreadStart(() =>
        {
            Console.WriteLine("Hello from example thread");
        });

        Thread th1 = new Thread(doTask);
        Thread th2 = new Thread(doTask);

        th1.Start();
        th2.Start();

        Console.WriteLine("Hello from main thread");
    }
}
