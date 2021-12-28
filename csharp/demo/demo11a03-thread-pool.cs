/*
 * THREAD POOLS
 * Version A03: Returning values
 */
using System;
using System.Threading;



class Demo11A03 : IRunnable
{
    public void run()
    {
        int[] arg = new int[2];
        arg[0] = 7; // input

        ThreadPool.QueueUserWorkItem(getSquared, arg);
        Thread.Sleep(1000);

        int result = arg[1];
        Console.WriteLine(result);
    }


    private void getSquared(dynamic arg)
    {
        int i = arg[0];
        arg[1] = i * i;
    }
}
