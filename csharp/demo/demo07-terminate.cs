/*
 * FORCING A THREAD TO TERMINATE (i.e. killing the thread)
 * Using a flag to notify the thread
 *
 * Note: The "volatile" keyword is explained in another demo.
 */
using System;
using System.Threading;



class Demo07 : IRunnable
{
    static volatile bool flagStop;

    public void run()
    {
        flagStop = false;

        var th = new Thread(() => {
            while (true)
            {
                if (flagStop)
                    break;

                Console.WriteLine("Running...");

                Thread.Sleep(1000);
            }
        });

        th.Start();

        Thread.Sleep(3000);

        flagStop = true;
    }
}
