/*
 * BLOCKING QUEUES
 * Version B: A fast producer and a slow consumer
 */
using System;
using System.Collections.Concurrent;
using System.Threading;



class Demo22B : IRunnable
{
    public void run()
    {
        // blocking queue with capacity = 2
        var queue = new BlockingCollection<string>(2);

        new Thread(() => producer(queue)).Start();
        new Thread(() => consumer(queue)).Start();

        // should call queue.Dispose();
    }


    private void producer(BlockingCollection<string> queue)
    {
        queue.Add("lorem");
        queue.Add("ipsum");

        /*
         * Due to reaching the maximum of capacity = 2, when executing bc.put("fooooooo"),
         * this thread is going to sleep until the queue removes an element.
        */

        queue.Add("fooooooo");
    }


    private void consumer(BlockingCollection<string> queue)
    {
        string data;
        Thread.Sleep(2000);

        for (int i = 0; i < 3; ++i)
        {
            Console.WriteLine("\nWaiting for data...");

            data = queue.Take();

            Console.WriteLine("    " + data);
        }
    }
}
