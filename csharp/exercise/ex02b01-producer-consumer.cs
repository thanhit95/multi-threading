/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE B: USING SEMAPHORES
 *      Version B01: 1 slow producer, 1 fast consumer
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer02B01 : IRunnable
{
    public void run()
    {
        var semFill = new Semaphore(0, 100);     // item produced
        var semEmpty = new Semaphore(1, 100);    // remaining space in queue

        var queue = new Queue<int>();

        new Thread(() => producer(semFill, semEmpty, queue)).Start();
        new Thread(() => consumer(semFill, semEmpty, queue)).Start();
    }


    private void producer(Semaphore semFill, Semaphore semEmpty, Queue<int> queue)
    {
        int i = 1;

        for (; ; ++i)
        {
            semEmpty.WaitOne();

            queue.Enqueue(i);
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
