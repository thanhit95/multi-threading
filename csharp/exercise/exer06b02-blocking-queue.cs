/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version B02: General blocking queues
 *              Underlying mechanism: Condition variables
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer06B02 : IRunnable
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

        foreach (var data in arr)
        {
            queue.put(data);
            Console.WriteLine($"Producer: {data}\t\t\t[done]");
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
        private object condEmpty = new object();
        private object condFull = new object();

        private int capacity = 0;
        private Queue<T> queue = null;


        public MyBlockingQueue(int capacity)
        {
            if (capacity <= 0)
                throw new ArgumentException("capacity must be a positive integer");

            this.capacity = capacity;
            queue = new Queue<T>();
        }


        public void put(T value)
        {
            lock (condFull)
            {
                while (queue.Count >= capacity)
                {
                    // Queue is full, must wait for 'take'
                    Monitor.Wait(condFull);
                }

                lock (queue)
                {
                    queue.Enqueue(value);
                }
            }

            lock (condEmpty)
            {
                Monitor.Pulse(condEmpty);
            }
        }


        public T take()
        {
            T result = default;

            lock (condEmpty)
            {
                while (0 == queue.Count)
                {
                    // Queue is empty, must wait for 'put'
                    Monitor.Wait(condEmpty);
                }

                lock (queue)
                {
                    result = queue.Dequeue();
                }
            }

            lock (condFull)
            {
                Monitor.Pulse(condFull);
            }

            return result;
        }
    }
}
