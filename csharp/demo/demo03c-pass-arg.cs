/*
 * PASSING ARGUMENTS
 * Version C: Traditional way + dynamic data type
 */
using System;
using System.Threading;



class Demo03B : IRunnable
{
    public void run()
    {
        Thread th1 = new Thread(new ParameterizedThreadStart(routine));
        Thread th2 = new Thread(new ParameterizedThreadStart(routine));

        th1.Start(new object[] { 1, 2, "red" });
        th2.Start(new object[] { 3, 4, "blue" });
    }

    private void routine(dynamic arg)
    {
        int a = arg[0];
        double b = arg[1];
        string c = arg[2];
        Console.WriteLine($"{a} {b} {c}\n");
    }
}
