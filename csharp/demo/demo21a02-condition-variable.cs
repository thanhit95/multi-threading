/*
 * CONDITION VARIABLES
 */
using System;
using System.Threading;



class Demo21A02 : IRunnable
{
    public void run()
    {
        var conditionVar = new object();

        ThreadStart foo = () =>
        {
            Console.WriteLine("foo is waiting...");

            lock (conditionVar)
            {
                Monitor.Wait(conditionVar);
            }

            Console.WriteLine("foo resumed");
        };

        ThreadStart bar = () =>
        {
            for (int i = 0; i < 3; ++i)
            {
                Thread.Sleep(2000);

                lock (conditionVar)
                {
                    Monitor.Pulse(conditionVar);
                }
            }
        };

        for (int i = 0; i < 3; ++i)
            new Thread(foo).Start();

        new Thread(bar).Start();
    }
}
