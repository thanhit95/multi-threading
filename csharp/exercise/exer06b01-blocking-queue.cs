/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version B01: General blocking queues
 *              Underlying mechanism: Semaphores
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer06B01 : IRunnable
{
    public void run()
    {
        var queue = new MyBlockingQueue<string>(2); // capacity = 2
        new Thread(() => producer(queue)).Start();
        new Thread(() => consumer(queue)).Start();
    }


    private void producer(MyBlockingQueue<string> queue)
    {
        string[] arr = { "nice", "to", "meet", "you" };

        foreach (var value in arr)
        {
            Console.WriteLine($"Producer: {value}");
            queue.put(value);
            Console.WriteLine($"Producer: {value}\t\t\t[done]");
        }
    }


    private void consumer(MyBlockingQueue<string> queue)
    {
        string data;
        Thread.Sleep(5000);

        for (int i = 0; i < 4; ++i)
        {
            data = queue.take();
            Console.WriteLine($"\tConsumer: {data}");

            if (0 == i)
                Thread.Sleep(5000);
        }
    }


    //////////////////////////////////////////////


    class MyBlockingQueue<T>
    {
        private Semaphore semRemain = null;
        private Semaphore semFill = null;

        private int capacity = 0;
        private Queue<T> queue = null;


        public MyBlockingQueue(int capacity)
        {
            if (capacity <= 0)
                throw new ArgumentException("capacity must be a positive integer");

            semRemain = new Semaphore(capacity, capacity);
            semFill = new Semaphore(0, capacity);

            this.capacity = capacity;
            queue = new Queue<T>();
        }


        public void put(T value)
        {
            semRemain.WaitOne();

            lock (queue)
            {
                queue.Enqueue(value);
            }

            semFill.Release();
        }


        public T take()
        {
            T result = default;
            semFill.WaitOne();

            lock (queue) {
                result = queue.Dequeue();
            }

            semRemain.Release();
            return result;
        }
    }
}
