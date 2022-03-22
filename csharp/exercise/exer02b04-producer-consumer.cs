/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORES
 *      Version B04: Multiple fast producers, multiple slow consumers
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer02B04 : IRunnable
{
    public void run()
    {
        var semFill = new Semaphore(0, int.MaxValue);     // item produced
        var semEmpty = new Semaphore(1, int.MaxValue);    // remaining space in queue

        var queue = new Queue<int>();

        const int NUM_PRODUCERS = 3;
        const int NUM_CONSUMERS = 2;


        var lstThProducer = new List<Thread>();
        var lstThConsumer = new List<Thread>();

        for (int i = 0; i < NUM_PRODUCERS; ++i)
        {
            int t = i;
            lstThProducer.Add(new Thread(() => producer(semFill, semEmpty, queue, t * 1000)));
        }

        for (int i = 0; i < NUM_CONSUMERS; ++i)
        {
            lstThConsumer.Add(new Thread(() => consumer(semFill, semEmpty, queue)));
        }


        lstThProducer.ForEach(th => th.Start());
        lstThConsumer.ForEach(th => th.Start());
    }


    private void producer(Semaphore semFill, Semaphore semEmpty,
        Queue<int> queue, int startValue)
    {
        int i = 1;

        for (; ; ++i)
        {
            semEmpty.WaitOne();
            queue.Enqueue(i + startValue);
            semFill.Release();
        }
    }


    private void consumer(Semaphore semFill, Semaphore semEmpty, Queue<int> queue)
    {
        for (; ; )
        {
            semFill.WaitOne();

            int data = queue.Dequeue();
            Console.WriteLine("Consumer " + data);
            Thread.Sleep(1000);

            semEmpty.Release();
        }
    }
}
