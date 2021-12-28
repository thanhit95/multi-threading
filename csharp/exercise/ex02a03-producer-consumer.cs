/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE A: USING BLOCKING QUEUES
 *      Version A03: 1 slow producer, 2 fast consumers
 */
using System;
using System.Collections.Concurrent;
using System.Threading;



class Exer02A03 : IRunnable
{
    public void run()
    {
        var qProduct = new BlockingCollection<int>(100);

        new Thread(() => funcProducer(qProduct)).Start();

        new Thread(() => funcConsumer("foo", qProduct)).Start();
        new Thread(() => funcConsumer("bar", qProduct)).Start();
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


    private void funcConsumer(string name, BlockingCollection<int> qProduct)
    {
        for (; ; )
        {
            int data = qProduct.Take();
            Console.WriteLine($"Consumer {name}: {data}");
        }
    }
}
