/*
 * CONDITION VARIABLES
 */
using System;
using System.Threading;



class Demo21A03 : IRunnable
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
            Thread.Sleep(3000);

            lock (conditionVar)
            {
                // Notify all waiting threads
                Monitor.PulseAll(conditionVar);
            }
        };

        for (int i = 0; i < 3; ++i)
            new Thread(foo).Start();

        new Thread(bar).Start();
    }
}
