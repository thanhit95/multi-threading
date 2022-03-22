/*
 * SEMAPHORES
 * Version B: Tires and chassis
 */
using System;
using System.Threading;



class Demo20B : IRunnable
{
    public void run()
    {
        var semTire = new Semaphore(4, int.MaxValue);
        var semChassis = new Semaphore(0, int.MaxValue);


        ThreadStart makeTire = () =>
        {
            for (int i = 0; i < 8; ++i)
            {
                semTire.WaitOne();

                Console.WriteLine("Make 1 tire");
                Thread.Sleep(1000);

                semChassis.Release();
            }
        };


        ThreadStart makeChassis = () =>
        {
            for (int i = 0; i < 4; ++i)
            {
                semChassis.WaitOne();
                semChassis.WaitOne();
                semChassis.WaitOne();
                semChassis.WaitOne();

                Console.WriteLine("Make 1 chassis");
                Thread.Sleep(3000);

                semTire.Release();
                semTire.Release();
                semTire.Release();
                semTire.Release();
            }
        };


        new Thread(makeTire).Start();
        new Thread(makeTire).Start();
        new Thread(makeChassis).Start();
    }
}
