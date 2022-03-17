/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A04: Multiple fast producers, multiple slow consumers
 */
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;



class Exer02A04 : IRunnable
{
    public void run()
    {
        var queue = new BlockingCollection<int>(5);

        const int NUM_PRODUCERS = 3;
        const int NUM_CONSUMERS = 2;

        var lstThProducer = new List<Thread>();
        var lstThConsumer = new List<Thread>();

        for (int i = 0; i < NUM_PRODUCERS; ++i)
        {
            int t = i;
            lstThProducer.Add(new Thread(() => producer(queue, t * 1000)));
        }

        for (int i = 0; i < NUM_CONSUMERS; ++i)
        {
            lstThConsumer.Add(new Thread(() => consumer(queue)));
        }

        lstThProducer.ForEach(th => th.Start());
        lstThConsumer.ForEach(th => th.Start());
    }


    private void producer(BlockingCollection<int> queue, int startValue)
    {
        int i = 1;
        if (startValue == 2000)
        {
            Console.WriteLine("FUCK IT");
        }

        for (; ; ++i)
        {
            queue.Add(i + startValue);
        }
    }


    private void consumer(BlockingCollection<int> queue)
    {
        for (; ; )
        {
            int data = queue.Take();
            Console.WriteLine("Consumer " + data);
            Thread.Sleep(1000);
        }
    }
}
