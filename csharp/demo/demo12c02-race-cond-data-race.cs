/*
 * RACE CONDITIONS AND DATA RACES
 */
using System;
using System.Threading;



class Demo12C02 : IRunnable
{
    public void run()
    {
        var thA = new Thread(() =>
        {
            Thread.Sleep(30);

            while (Global.counter < 10)
                ++Global.counter;

            Console.WriteLine("A won !!!");
        });


        var thB = new Thread(() =>
        {
            Thread.Sleep(30);

            while (Global.counter > -10)
                --Global.counter;

            Console.WriteLine("B won !!!");
        });


        thA.Start();
        thB.Start();
    }


    class Global
    {
        public static int counter = 0;
    }
}
