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
        var semFill = new Semaphore(0, 100);     // item produced
        var semEmpty = new Semaphore(1, 100);    // remaining space in queue

        var qProduct = new Queue<int>();

        const int NUM_PRODUCERS = 3;
        const int NUM_CONSUMERS = 2;


        var lstProd = new List<Thread>();
        var lstCons = new List<Thread>();

        for (int i = 0; i < NUM_PRODUCERS; ++i)
        {
            int t = i;
            lstProd.Add(new Thread(() => funcProducer(semFill, semEmpty, qProduct, t * 1000)));
        }

        for (int i = 0; i < NUM_CONSUMERS; ++i)
        {
            lstCons.Add(new Thread(() => funcConsumer(semFill, semEmpty, qProduct)));
        }


        lstProd.ForEach(th => th.Start());
        lstCons.ForEach(th => th.Start());
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
