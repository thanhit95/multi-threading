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
        var queue = new BlockingCollection<int>(1);

        new Thread(() => producer(queue)).Start();

        new Thread(() => consumer("foo", queue)).Start();
        new Thread(() => consumer("bar", queue)).Start();
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


    private void consumer(string name, BlockingCollection<int> queue)
    {
        for (; ; )
        {
            int data = queue.Take();
            Console.WriteLine($"Consumer {name}: {data}");
        }
    }
}
