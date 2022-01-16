/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A: Using functions
 */
using System;
using System.Threading;



class Demo01A : IRunnable
{
    public void run()
    {
        Thread th = new Thread(doTask);
        // or
        // Thread th = new Thread(new ThreadStart(doTask));

        th.Start();
        Console.WriteLine("Hello from main thread");
    }

    private void doTask()
    {
        Console.WriteLine("Hello from example thread");
    }
}
