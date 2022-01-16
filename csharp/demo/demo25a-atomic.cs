/*
 * ATOMIC ACCESS
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Demo25A : IRunnable
{
    public void run()
    {
        ThreadStart doTask = () =>
        {
            Thread.Sleep(1000);
            Global.counter += 1;
        };


        var lstTh = new List<Thread>();

        for (int i = 0; i < 1000; ++i)
            lstTh.Add(new Thread(doTask));


        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());


        // Unpredictable result
        Console.WriteLine("counter = " + Global.counter);
    }


    class Global
    {
        public static volatile int counter = 0;
    }
}
