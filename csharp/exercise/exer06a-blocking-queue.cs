/*
 * BLOCKING QUEUE IMPLEMENTATION
 * Version A: Synchronous queues
 */
using System;
using System.Threading;



class Exer06A : IRunnable
{
    public void run()
    {
        var queue = new MySynchronousQueue<string>();
        new Thread(() => producer(queue)).Start();
        new Thread(() => consumer(queue)).Start();
    }


    private void producer(MySynchronousQueue<string> queue)
    {
        string[] arr = { "lorem", "ipsum", "dolor" };

        foreach (var data in arr)
        {
            Console.WriteLine($"Producer: {data}");
            queue.put(data);
            Console.WriteLine($"Producer: {data}\t\t\t[done]");
        }
    }


    private void consumer(MySynchronousQueue<string> queue)
    {
        string data;
        Thread.Sleep(5000);

        for (int i = 0; i < 3; ++i)
        {
            data = queue.take();
            Console.WriteLine($"\tConsumer: {data}");
        }
    }


    class MySynchronousQueue<T>
    {
        private Semaphore semPut = new Semaphore(1, int.MaxValue);
        private Semaphore semTake = new Semaphore(0, int.MaxValue);
        private T element = default;


        public void put(T value)
        {
            semPut.WaitOne();
            element = value;
            semTake.Release();
        }


        public T take()
        {
            semTake.WaitOne();

            T result = element;
            element = default;

            semPut.Release();

            return result;
        }
    }
}
