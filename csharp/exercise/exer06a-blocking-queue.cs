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
        string[] arr = { "lorem", "ipsum", "foo" };

        foreach (var value in arr)
        {
            Console.WriteLine($"Producer: {value}");
            queue.put(value);
            Console.WriteLine($"Producer: {value}\t\t\t[done]");
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
        private Semaphore semPut = new Semaphore(1, 100);
        private Semaphore semTake = new Semaphore(0, 100);
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
