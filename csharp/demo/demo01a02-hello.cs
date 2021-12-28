/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A02: Using class ThreadStart
 *
 * The difference between version A and version B:
 * "new Thread(lorem)" is just the abbreviation of "new Thread(new ThreadStart(lorem))"
 */
using System;
using System.Threading;



class Demo01A02 : IRunnable
{
    public void run()
    {
        Thread th = new Thread(new ThreadStart(lorem));
        th.Start();
        Console.WriteLine("Hello from main thread");
    }

    private void lorem()
    {
        Console.WriteLine("Hello from Lorem thread");
    }
}
