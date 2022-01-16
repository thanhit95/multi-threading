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
        Thread thFoo = new Thread(doTask);
        Thread thBar = new Thread(doTask);

        // or
        // Thread thFoo = new Thread(new ParameterizedThreadStart(doTask));
        // Thread thBar = new Thread(new ParameterizedThreadStart(doTask));

        thFoo.Start(new object[] { 1, 2.0, "red" });
        thBar.Start(new object[] { 3, 4.0, "blue" });
    }

    private void doTask(object arg)
    {
        object[] array = (object[]) arg;

        int a = (int) array[0];
        double b = (double) array[1];
        string c = (string) array[2];

        Console.WriteLine($"{a} {b} {c}\n");
    }
}
