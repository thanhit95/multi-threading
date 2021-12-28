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
        var semFill = new Semaphore(0, 100);     // item produced
        var semEmpty = new Semaphore(1, 100);    // remaining space in queue

        var qProduct = new Queue<int>();

        new Thread(() => funcProducer(semFill, semEmpty, qProduct, 0)).Start();
        new Thread(() => funcProducer(semFill, semEmpty, qProduct, 100)).Start();

        new Thread(() => funcConsumer(semFill, semEmpty, qProduct)).Start();
    }


    private void funcProducer(Semaphore semFill, Semaphore semEmpty,
        Queue<int> qProduct, int startValue)
    {
        int i = 1;

        for (; ; ++i)
        {
            semEmpty.WaitOne();
            qProduct.Enqueue(i + startValue);
            semFill.Release();
        }
    }


    private void funcConsumer(Semaphore semFill, Semaphore semEmpty, Queue<int> qProduct)
    {
        for (; ; )
        {
            semFill.WaitOne();

            int data = qProduct.Dequeue();
            Console.WriteLine("Consumer " + data);
            Thread.Sleep(1000);

            semEmpty.Release();
        }
    }
}
