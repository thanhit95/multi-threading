/*
 * THREAD YIELDING
 */
using System;
using System.Threading;



class Demo10 : IRunnable
{
    public void run()
    {
        DateTime tpStartMeasure = DateTime.Now;

        littleSleep(1);

        var timeElapsed = DateTime.Now.Subtract(tpStartMeasure).TotalMilliseconds;

        Console.WriteLine($"Elapsed time: {timeElapsed} miliseonds");
    }


    private void littleSleep(double miliseconds)
    {
        DateTime tpEnd = DateTime.Now.AddMilliseconds(miliseconds);

        do
        {
            Thread.Yield();
        }
        while (DateTime.Now.CompareTo(tpEnd) < 0);
    }
}
