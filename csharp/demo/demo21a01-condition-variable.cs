/*
 * CONDITION VARIABLES
 *
 * In my opinion, the best mechanism to demonstrate term "Condition Variable"
 * in C# is System.Threading.Monitor.
 *
 * Monitor.Wait(conditionVariable)      ==> Wait
 * Monitor.Pulse(conditionVariable)     ==> Notify
 * Monitor.PulseAll(conditionVariable)  ==> Notify All
 */
using System;
using System.Threading;



class Demo21A01 : IRunnable
{
    public void run()
    {
        var conditionVar = new object();

        ThreadStart foo = () =>
        {
            Console.WriteLine("foo is waiting...");

            lock (conditionVar)
            {
                // Waiting for notification from conditionVar
                Monitor.Wait(conditionVar);
            }

            Console.WriteLine("foo resumed");
        };

        ThreadStart bar = () =>
        {
            Thread.Sleep(3000);

            lock (conditionVar)
            {
                // Notify a thread which is waiting for notification from conditionVar
                Monitor.Pulse(conditionVar);
            }
        };

        new Thread(foo).Start();
        new Thread(bar).Start();
    }
}
