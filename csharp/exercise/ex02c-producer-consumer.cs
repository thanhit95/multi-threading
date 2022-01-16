/*
 * THE PRODUCER-CONSUMER PROBLEM
 *
 * SOLUTION TYPE C: USING CONDITION VARIABLES & CUSTOM MONITORS
 *      Multiple fast producers, multiple slow consumers
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer02C : IRunnable
{
    public void run()
    {
        var monitor = new ProdConsMonitor<int>();
        var queue = new Queue<int>();


        const int MAX_QUEUE_SIZE = 6;
        const int NUM_PRODUCERS = 3;
        const int NUM_CONSUMERS = 2;


        monitor.init(MAX_QUEUE_SIZE, queue);


        var lstProd = new List<Thread>();
        var lstCons = new List<Thread>();

        for (int i = 0; i < NUM_PRODUCERS; ++i)
        {
            int t = i;
            lstProd.Add(new Thread(() => producer(monitor, t * 1000)));
        }

        for (int i = 0; i < NUM_CONSUMERS; ++i)
        {
            lstCons.Add(new Thread(() => consumer(monitor)));
        }


        lstProd.ForEach(th => th.Start());
        lstCons.ForEach(th => th.Start());
    }


    private void producer(ProdConsMonitor<int> monitor, int startValue)
    {
        int i = 1;

        for (; ; ++i)
        {
            monitor.add(i + startValue);
        }
    }


    private void consumer(ProdConsMonitor<int> monitor)
    {
        for (; ; )
        {
            int data = monitor.remove();
            Console.WriteLine("Consumer " + data);
            Thread.Sleep(1000);
        }
    }


    class ProdConsMonitor<T>
    {
        private Queue<T> queue;
        private int maxQueueSize;

        private object condFull = new object();
        private object condEmpty = new object();


        public void init(int maxQueueSize, Queue<T> queue)
        {
            this.maxQueueSize = maxQueueSize;
            this.queue = queue;
        }


        public void add(T item)
        {
            lock (condFull)
            {
                while (queue.Count == maxQueueSize)
                    Monitor.Wait(condFull);

                queue.Enqueue(item);
            }

            lock (condEmpty)
            {
                if (queue.Count == 1)
                    Monitor.Pulse(condEmpty);
            }
        }


        public T remove()
        {
            T item = default;

            lock (condEmpty)
            {
                while (queue.Count == 0)
                    Monitor.Wait(condEmpty);

                item = queue.Dequeue();
            }

            lock (condFull)
            {
                if (queue.Count == maxQueueSize - 1)
                    Monitor.Pulse(condFull);
            }

            return item;
        }
    }
}
