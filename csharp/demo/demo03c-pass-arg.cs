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
        Thread thFoo = new Thread(doTask);
        Thread thBar = new Thread(doTask);

        thFoo.Start(new object[] { 1, 2, "red" });
        thBar.Start(new object[] { 3, 4, "blue" });
    }

    private void doTask(dynamic arg)
    {
        int a = arg[0];
        double b = arg[1];
        string c = arg[2];
        Console.WriteLine($"{a} {b} {c}\n");
    }
}
