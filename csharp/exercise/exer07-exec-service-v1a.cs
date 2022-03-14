/*
 * MY EXECUTOR SERVICE
 *
 * Version 1A: Simple executor service
 * - Method "waitTaskDone" consumes CPU (due to bad synchronization).
 */
using System;
using System.Collections.Generic;
using System.Threading;



namespace Exer07
{
    class MyExecServiceV1A
    {
        private int numThreads = 0;
        private List<Thread> lstTh = new List<Thread>();

        private Queue<IRunnable> taskPending = new Queue<IRunnable>();
        private int counterTaskRunning = 0;

        private volatile bool forceThreadShutdown = false;



        public MyExecServiceV1A(int numThreads) {
            init(numThreads);
        }



        private void init(int inpNumThreads)
        {
            // shutdown();

            numThreads = inpNumThreads;
            Interlocked.Exchange(ref counterTaskRunning, 0);
            forceThreadShutdown = false;

            for (int i = 0; i < numThreads; ++i)
                lstTh.Add(new Thread(() => threadWorkerFunc(this)));

            lstTh.ForEach(th => th.Start());
        }



        public void submit(IRunnable task)
        {
            lock (taskPending)
            {
                taskPending.Enqueue(task);
                Monitor.Pulse(taskPending);
            }
        }



        public void waitTaskDone()
        {
            bool done = false;

            for (; ; )
            {
                lock (taskPending)
                {
                    if (0 == taskPending.Count && 0 == counterTaskRunning)
                    {
                        done = true;
                    }
                }

                if (done)
                    break;

                Thread.Yield();
            }
        }



        public void shutdown()
        {
            lock (taskPending)
            {
                forceThreadShutdown = true;
                taskPending.Clear();
                Monitor.PulseAll(taskPending);
            }

            lstTh.ForEach(th => th.Join());

            numThreads = 0;
            lstTh.Clear();
        }



        private static void threadWorkerFunc(MyExecServiceV1A thisPtr)
        {
            ref var taskPending = ref thisPtr.taskPending;
            ref var counterTaskRunning = ref thisPtr.counterTaskRunning;

            IRunnable task = null;

            for (; ; )
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                lock (taskPending)
                {
                    while (0 == taskPending.Count && false == thisPtr.forceThreadShutdown)
                    {
                        Monitor.Wait(taskPending);
                    }

                    if (thisPtr.forceThreadShutdown)
                    {
                        break;
                    }

                    // GET THE TASK FROM THE PENDING QUEUE
                    task = taskPending.Dequeue();

                    Interlocked.Increment(ref counterTaskRunning);
                }

                // DO THE TASK
                task.run();
                Interlocked.Decrement(ref counterTaskRunning);
            }
        }
    }
}
