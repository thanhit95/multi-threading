/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A01: Using functions
 */
using System;
using System.Threading;



class Demo01A01 : IRunnable
{
    public void run()
    {
        Thread th = new Thread(lorem);
        th.Start();
        Console.WriteLine("Hello from main thread");
    }

    private void lorem()
    {
        Console.WriteLine("Hello from Lorem thread");
    }
}
