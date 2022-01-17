/*
 * THREAD JOINS
 */
using System;
using System.Threading;



class Demo02A : IRunnable
{
    public void run()
    {
        Thread th = new Thread(doHeavyTask);

        th.Start();
        th.Join();

        Console.WriteLine("Good bye!");
    }

    private void doHeavyTask() {
        // Do a heavy task, which takes a little time
        for (int i = 0; i < 2000000000; ++i);

        Console.WriteLine("Done!");
    }
}
