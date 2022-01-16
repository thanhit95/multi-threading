/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version extra: Getting thread's name
 */
using System;
using System.Threading;



class Demo01ExtraName : IRunnable
{
    public void run()
    {
        Thread thFoo = new Thread(doTask)
        {
            Name = "foo"
        };

        Thread thBar = new Thread(doTask);
        thBar.Name = "bar";

        thFoo.Start();
        thBar.Start();
    }

    private void doTask()
    {
        Console.WriteLine($"My name is {Thread.CurrentThread.Name}");
    }
}
