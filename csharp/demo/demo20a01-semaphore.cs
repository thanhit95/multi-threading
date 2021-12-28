/*
 * SEMAPHORES
 * Version A: Paper sheets and packages
 */
using System;
using System.Threading;



class Demo20A01 : IRunnable
{
    public void run()
    {
        var semPackage = new Semaphore(0, 8); // initialCount = 0, maximumCount = 8


        ThreadStart makeOneSheet = () =>
        {
            for (int i = 0; i < 4; ++i)
            {
                Console.WriteLine("Make 1 sheet");
                Thread.Sleep(1000);
                semPackage.Release();
            }
        };


        ThreadStart combineOnePackage = () =>
        {
            for (int i = 0; i < 4; ++i)
            {
                semPackage.WaitOne();
                semPackage.WaitOne();
                Console.WriteLine("Combine 2 sheets into 1 package");
            }
        };


        new Thread(makeOneSheet).Start();
        new Thread(makeOneSheet).Start();
        new Thread(combineOnePackage).Start();
    }
}
