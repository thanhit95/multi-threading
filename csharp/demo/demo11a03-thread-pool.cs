/*
 * THREAD POOLS
 * Version A03: System.Threading.ThreadPool
 *              Returning values
 */
using System;
using System.Threading;



class Demo11A03 : IRunnable
{
    private AutoResetEvent re;


    public void run()
    {
        re = new AutoResetEvent(false);

        int[] arg = new int[2];
        arg[0] = 7; // input

        ThreadPool.QueueUserWorkItem(getSquared, arg);

        // Wait until the thread completes
        re.WaitOne();

        int result = arg[1];
        Console.WriteLine(result);
    }


    private void getSquared(dynamic arg)
    {
        int i = arg[0];
        arg[1] = i * i;
        re.Set();
    }
}
