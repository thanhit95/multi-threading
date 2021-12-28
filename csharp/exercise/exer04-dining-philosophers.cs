/*
 * THE DINING PHILOSOPHERS PROBLEM
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer04 : IRunnable
{
    public void run()
    {
        const int NUM_PHILOSOPHERS = 5;


        var chopstick = new Semaphore[NUM_PHILOSOPHERS];

        for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
            chopstick[i] = new Semaphore(1, NUM_PHILOSOPHERS + 1);


        var lstTh = new List<Thread>();

        for (int ith = 0; ith < NUM_PHILOSOPHERS; ++ith)
        {
            int i = ith;

            lstTh.Add(new Thread(() =>
            {
                int n = NUM_PHILOSOPHERS;
                Thread.Sleep(1000);

                chopstick[i].WaitOne();
                chopstick[(i + 1) % n].WaitOne();

                Console.WriteLine($"Philosopher #{i} is eating the rice");

                chopstick[(i + 1) % n].Release();
                chopstick[i].Release();
            }));
        }


        lstTh.ForEach(th => th.Start());
    }
}
