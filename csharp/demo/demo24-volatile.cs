/*
 * THE VOLATILE KEYWORD
 */
using System;
using System.Threading;



class Demo24 : IRunnable
{
    public void run()
    {
        Global.isRunning = true;
        new Thread(doTask).Start();

        Thread.Sleep(6000);
        Global.isRunning = false;
    }


    private void doTask()
    {
        while (Global.isRunning)
        {
            Console.WriteLine("Running...");
            Thread.Sleep(2000);
        }
    }


    class Global
    {
        public static volatile bool isRunning;
    }
}
