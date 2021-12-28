/*
 * REENTRANT LOCKS (RECURSIVE MUTEXES)
 *
 * In C#, "lock" keyword and System.Threading.Monitor class allow re-entrancy.
 * That means they are reentrant locks by default.
 */
using System;
using System.Threading;



class Demo17 : IRunnable
{
    public void run()
    {
        Console.WriteLine("No demo here");
    }
}
