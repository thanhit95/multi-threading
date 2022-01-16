/*
 * INTRODUCTION TO MULTITHREADING
 * You should try running this app several times and see results.
 */
using System;
using System.Threading;



class Demo00 : IRunnable
{
    public void run()
    {
        Thread th = new Thread(doTask);

        th.Start();

        for (int i = 0; i < 300; ++i)
            Console.Write("A");
    }

    private void doTask()
    {
        for (int i = 0; i < 300; ++i)
            Console.Write("B");
    }
}
