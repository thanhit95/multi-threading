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

        var thFoo = new Thread(doTask);
        var thBar = new Thread(doTask);
        var thEgg = new Thread(doTask);

        thFoo.Start();
        thBar.Start();
        thEgg.Start();

        thFoo.Join();
        thBar.Join();
        thEgg.Join();

        Console.WriteLine("counter = " + counter);
        /*
         * We are not sure that counter = 1500
         */
    }


    private void doTask()
    {
        for (int i = 0; i < 500; ++i)
        {
            Thread.Sleep(3);
            counter += 1;
        }
    }
}
