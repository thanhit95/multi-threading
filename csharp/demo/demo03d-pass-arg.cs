/*
 * PASSING ARGUMENTS
 * Version D: Passing arguments by capturing them
 */
using System;
using System.Threading;



class Demo03D : IRunnable
{
    public void run()
    {
        const int COUNT = 10;

        Thread th = new Thread(() =>
        {
            for (int i = 1; i <= COUNT; ++i)
                Console.WriteLine("Foo " + i);
        });

        th.Start();
    }
}
