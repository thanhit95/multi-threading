/*
 * DEADLOCK
 * Version A
 */
using System;
using System.Threading;



class Demo15A : IRunnable
{
    private Mutex mut;


    public void run()
    {
        mut = new Mutex();

        var thFoo = new Thread(() => routine("foo"));
        var thBar = new Thread(() => routine("bar"));

        thFoo.Start();
        thBar.Start();

        thFoo.Join();
        thBar.Join();

        // The app may throw System.Threading.AbandonedMutexException
        Console.WriteLine("You will never see this statement due to deadlock!");
    }


    private void routine(string name)
    {
        mut.WaitOne();

        Console.WriteLine(name + " acquired resource");

        // mut.ReleaseMutex(); // forget this statement ==> deadlock
    }
}
