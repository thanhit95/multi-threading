/*
 * PASSING ARGUMENTS
 * Version B: Traditional way with a single argument of type object
 */
using System;
using System.Threading;



class Demo03A : IRunnable
{
    public void run()
    {
        Thread th1 = new Thread(new ParameterizedThreadStart(routine));
        Thread th2 = new Thread(new ParameterizedThreadStart(routine));

        th1.Start(new object[] { 1, 2.0, "red" });
        th2.Start(new object[] { 3, 4.0, "blue" });
    }

    private void routine(object arg)
    {
        object[] array = (object[]) arg;
        int a = (int) array[0];
        double b = (double) array[1];
        string c = (string) array[2];

        Console.WriteLine($"{a} {b} {c}\n");
    }
}
