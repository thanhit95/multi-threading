/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A02: 2 slow producers, 1 fast consumer
 */
using System;
using System.Collections.Concurrent;
using System.Threading;



class Exer02A02 : IRunnable
{
    public void run()
    {
        var qProduct = new BlockingCollection<int>(100);

        new Thread(() => funcProducer(qProduct)).Start();
        new Thread(() => funcProducer(qProduct)).Start();

        new Thread(() => funcConsumer(qProduct)).Start();
    }


    private void funcProducer(BlockingCollection<int> qProduct)
    {
        int i = 1;

        for (; ; ++i)
        {
            qProduct.Add(i);
            Thread.Sleep(1000);
        }
    }


    private void funcConsumer(BlockingCollection<int> qProduct)
    {
        for (; ; )
        {
            int data = qProduct.Take();
            Console.WriteLine("Consumer " + data);
        }
    }
}
