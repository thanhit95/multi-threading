/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORES
 *      Version B03: 2 fast producers, 1 slow consumer
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer02B03 : IRunnable
{
    public void run()
    {
        var semFill = new Semaphore(0, int.MaxValue);     // item produced
        var semEmpty = new Semaphore(1, int.MaxValue);    // remaining space in queue

        var queue = new Queue<int>();

        new Thread(() => producer(semFill, semEmpty, queue, 0)).Start();
        new Thread(() => producer(semFill, semEmpty, queue, 1000)).Start();

        new Thread(() => consumer(semFill, semEmpty, queue)).Start();
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
