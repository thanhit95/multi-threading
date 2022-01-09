/*
 * LIST OF MULTIPLE THREADS
 * Version B: Using Linq
 */
using System;
using System.Linq;
using System.Threading;



class Demo06B : IRunnable
{
    public void run()
    {
        var lstTh = Enumerable.Range(0, 5).Select(index => new Thread(() =>
        {
            Thread.Sleep(500);
            Console.WriteLine(index);
        })).ToList();

        lstTh.ForEach(th => th.Start());
    }
}
