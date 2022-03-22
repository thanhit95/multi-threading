/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORES
 *      Version B02: 2 slow producers, 1 fast consumer
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer02B02 : IRunnable
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
            Thread.Sleep(1000);

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

            semEmpty.Release();
        }
    }
}
