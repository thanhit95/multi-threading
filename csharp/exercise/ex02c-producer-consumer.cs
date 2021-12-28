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
        var qProduct = new Queue<int>();


        const int MAX_QUEUE_SIZE = 6;
        const int NUM_PRODUCERS = 3;
        const int NUM_CONSUMERS = 2;


        monitor.init(MAX_QUEUE_SIZE, qProduct);


        var lstProd = new List<Thread>();
        var lstCons = new List<Thread>();

        for (int i = 0; i < NUM_PRODUCERS; ++i)
        {
            int t = i;
            lstProd.Add(new Thread(() => funcProducer(monitor, t * 1000)));
        }

        for (int i = 0; i < NUM_CONSUMERS; ++i)
        {
            lstCons.Add(new Thread(() => funcConsumer(monitor)));
        }


        lstProd.ForEach(th => th.Start());
        lstCons.ForEach(th => th.Start());
    }


    private void funcProducer(ProdConsMonitor<int> monitor, int startValue)
    {
        int i = 1;

        for (; ; ++i)
        {
            monitor.add(i + startValue);
        }
    }


    private void funcConsumer(ProdConsMonitor<int> monitor)
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
        private Queue<T> q;
        private int maxQueueSize;

        private object condFull = new object();
        private object condEmpty = new object();


        public void init(int maxQueueSize, Queue<T> q)
        {
            this.maxQueueSize = maxQueueSize;
            this.q = q;
        }


        public void add(T item)
        {
            lock (condFull)
            {
                while (q.Count == maxQueueSize)
                    Monitor.Wait(condFull);

                q.Enqueue(item);
            }

            lock (condEmpty)
            {
                if (q.Count == 1)
                    Monitor.Pulse(condEmpty);
            }
        }


        public T remove()
        {
            T item = default;

            lock (condEmpty)
            {
                while (q.Count == 0)
                    Monitor.Wait(condEmpty);

                item = q.Dequeue();
            }

            lock (condFull)
            {
                if (q.Count == maxQueueSize - 1)
                    Monitor.Pulse(condFull);
            }

            return item;
        }
    }
}
