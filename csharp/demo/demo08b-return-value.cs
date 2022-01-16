/*
 * GETTING RETURNED VALUES FROM THREADS
 * Using AutoResetEvent to notify the thread which is waiting for returned values
 */
using System;
using System.Threading;



class Demo08B : IRunnable
{
    private AutoResetEvent re;
    private int result;


    public void run()
    {
        re = new AutoResetEvent(false);

        new Thread(() => doubleValue(5)).Start();

        // Wait until we receive a notification from re
        re.WaitOne();

        Console.WriteLine(result);
    }


    private void doubleValue(int value)
    {
        result = value * 2;

        Thread.Sleep(2000);
        re.Set(); // Notify the threads that are waiting for re

        Thread.Sleep(2000);
        Console.WriteLine("This thread is exiting");
    }
}
