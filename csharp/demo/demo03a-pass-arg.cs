/*
 * PASSING ARGUMENTS
 * Version A: Using lambdas
 */
using System;
using System.Threading;



class Demo03C : IRunnable
{
    public void run()
    {
        Thread thFoo = new Thread(() => doTask(1, 2, "red"));
        Thread thBar = new Thread(() => doTask(3, 4, "blue"));

        thFoo.Start();
        thBar.Start();
    }


    private void doTask(int a, double b, string c)
    {
        Console.WriteLine($"{a} {b} {c}");
    }
}
