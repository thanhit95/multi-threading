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
        Thread th1 = new Thread(() => routine(1, 2, "red"));
        Thread th2 = new Thread(() => routine(3, 4, "blue"));

        th1.Start();
        th2.Start();
    }


    private void routine(int a, double b, string c)
    {
        Console.WriteLine($"{a} {b} {c}");
    }
}
