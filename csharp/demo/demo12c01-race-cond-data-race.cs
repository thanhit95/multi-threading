/*
 * RACE CONDITIONS AND DATA RACES
 */
using System;
using System.Threading;



class Demo12C01 : IRunnable
{
    private int counter;


    public void run()
    {
        counter = 0;

        var foo = new Thread(routine);
        var bar = new Thread(routine);

        foo.Start();
        bar.Start();
        foo.Join();
        bar.Join();

        Console.WriteLine("counter = " + counter);
        /*
         * We are not sure that counter = 1000
         */
    }


    private void routine()
    {
        for (int i = 0; i < 500; ++i)
        {
            Thread.Sleep(3);
            counter += 1;
        }
    }
}
