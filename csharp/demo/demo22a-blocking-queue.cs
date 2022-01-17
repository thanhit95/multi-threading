/*
 * BLOCKING QUEUES
 * Version A: A slow producer and a fast consumer
 */
using System;
using System.Collections.Concurrent;
using System.Threading;



class Demo22A : IRunnable
{
    public void run()
    {
        // blocking queue with capacity = 2
        var queue = new BlockingCollection<string>(2);

        new Thread(() => producer(queue)).Start();
        new Thread(() => consumer(queue)).Start();

        // Should call queue.Dispose();
    }


    private void producer(BlockingCollection<string> queue)
    {
        Thread.Sleep(2000);
        queue.Add("Alice");

        Thread.Sleep(2000);
        queue.Add("likes");

        Thread.Sleep(2000);
        queue.Add("singing");
    }


    private void consumer(BlockingCollection<string> queue)
    {
        string data;

        for (int i = 0; i < 3; ++i)
        {
            Console.WriteLine("\nWaiting for data...");

            data = queue.Take();

            Console.WriteLine("    " + data);
        }
    }
}
