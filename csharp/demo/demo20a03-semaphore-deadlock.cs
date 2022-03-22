/*
 * SEMAPHORES
 * Version A: Paper sheets and packages
 */
using System;
using System.Threading;



class Demo20A03 : IRunnable
{
    public void run()
    {
        var semPackage = new Semaphore(0, int.MaxValue);
        var semSheet = new Semaphore(2, int.MaxValue);


        ThreadStart makeOneSheet = () =>
        {
            for (int i = 0; i < 4; ++i)
            {
                semSheet.WaitOne();
                Console.WriteLine("Make 1 sheet");
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
                Thread.Sleep(1000);

                semSheet.Release();
                // Missing one statement: semSheet.Release() ==> deadlock
            }
        };


        new Thread(makeOneSheet).Start();
        new Thread(makeOneSheet).Start();
        new Thread(combineOnePackage).Start();
    }
}
