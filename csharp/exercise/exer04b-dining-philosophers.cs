/*
 * THE DINING PHILOSOPHERS PROBLEM
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer04B : IRunnable
{
    public void run()
    {
        const int NUM_PHILOSOPHERS = 5;


        var chopstick = new object[NUM_PHILOSOPHERS];

        for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
            chopstick[i] = new object();


        var lstTh = new List<Thread>();

        for (int ith = 0; ith < NUM_PHILOSOPHERS; ++ith)
        {
            int i = ith;

            lstTh.Add(new Thread(() =>
            {
                int n = NUM_PHILOSOPHERS;
                Thread.Sleep(1000);

                lock (chopstick[i])
                {
                    lock (chopstick[(i + 1) % n])
                    {
                        Console.WriteLine($"Philosopher #{i} is eating the rice");
                    }
                }
            }));
        }


        lstTh.ForEach(th => th.Start());
    }
}
