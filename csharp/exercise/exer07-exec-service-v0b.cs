/*
 * MY EXECUTOR SERVICE
 *
 * Version 0B: The easiest executor service
 * - It uses a blocking queue as underlying mechanism.
 * - It supports waitTaskDone() and shutdown().
 */
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;



namespace Exer07
{
    class MyExecServiceV0B
    {
        private int numThreads = 0;
        private List<Thread> lstTh = new List<Thread>();

        private BlockingCollection<IRunnable> taskPending = new BlockingCollection<IRunnable>();
        private int counterTaskRunning = 0;

        private volatile bool forceThreadShutdown = false;

        private class EmptyTask : IRunnable
        {
            public void run() { }
        }



        public MyExecServiceV0B(int numThreads) {
            init(numThreads);
        }



        private void init(int inpNumThreads)
        {
            numThreads = inpNumThreads;
            Interlocked.Exchange(ref counterTaskRunning, 0);
            forceThreadShutdown = false;

            for (int i = 0; i < numThreads; ++i)
                lstTh.Add(new Thread(() => threadWorkerFunc(this)));

            lstTh.ForEach(th => th.Start());
        }



        public void submit(IRunnable task)
        {
            taskPending.Add(task);
        }



        public void waitTaskDone()
        {
            // This ExecService is too simple,
            // so there is no good implementation for waitTaskDone()
            while (
                taskPending.Count > 0 ||
                Interlocked.CompareExchange(ref counterTaskRunning, 0, 0) > 0
            ) {
                Thread.Sleep(1000);
                // Thread.Yield();
            }
        }



        public void shutdown()
        {
            forceThreadShutdown = true;
            IRunnable temp;

            while (taskPending.Count > 0)
                taskPending.TryTake(out temp, 1000);

            // Invoke blocked threads by adding "empty" tasks
            for (int i = 0; i < numThreads; ++i)
                taskPending.Add(new EmptyTask());

            lstTh.ForEach(th => th.Join());

            numThreads = 0;
            lstTh.Clear();
        }



        private static void threadWorkerFunc(MyExecServiceV0B thisPtr)
        {
            ref var taskPending = ref thisPtr.taskPending;
            ref var counterTaskRunning = ref thisPtr.counterTaskRunning;
            IRunnable task = null;

            for (; ; )
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                task = taskPending.Take();

                // If shutdown() was called, then exit the function
                if (thisPtr.forceThreadShutdown)
                {
                    break;
                }

                // DO THE TASK
                Interlocked.Increment(ref counterTaskRunning);
                task.run();
                Interlocked.Decrement(ref counterTaskRunning);
            }
        }
    }
}
