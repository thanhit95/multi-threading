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
        var queue = new BlockingCollection<int>(1);

        new Thread(() => producer(queue)).Start();
        new Thread(() => producer(queue)).Start();

        new Thread(() => consumer(queue)).Start();
    }


    private void producer(BlockingCollection<int> queue)
    {
        int i = 1;

        for (; ; ++i)
        {
            queue.Add(i);
            Thread.Sleep(1000);
        }
    }


    private void consumer(BlockingCollection<int> queue)
    {
        for (; ; )
        {
            int data = queue.Take();
            Console.WriteLine("Consumer " + data);
        }
    }
}
