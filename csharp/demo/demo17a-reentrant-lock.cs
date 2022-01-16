/*
 * REENTRANT LOCKS (RECURSIVE MUTEXES)
 *
 * In C#, "lock" keyword and System.Threading.Monitor class allow re-entrancy.
 * That means they are reentrant locks by default.
 *
 * Version A: A simple example
 */
using System;
using System.Threading;



class Demo17A : IRunnable
{
    public void run()
    {
        const string resource = "resource";

        new Thread(() =>
        {
            lock (resource)
            {
                Console.WriteLine("First time acquiring the resource");

                lock (resource)
                {
                    Console.WriteLine("Second time acquiring the resource");
                }
            }
        }).Start();
    }
}
