/*
 * MY THREAD POOL
 *
 * Version 2B:
 *   - Better synchronization.
 *   - Method "waitTaskDone":
 *       + uses a condition variable to synchronize.
 *       + does not consume CPU (compared to version 1).
 */
using System;
using System.Collections.Generic;
using System.Threading;



namespace Exer07
{
    class MyThreadPoolV2B
    {
        private int numThreads = 0;
        private List<Thread> lstTh = new List<Thread>();

        private Queue<IRunnable> taskPending = new Queue<IRunnable>();
        private List<IRunnable> taskRunning = new List<IRunnable>();

        private volatile bool forceThreadShutdown = false;



        public void init(int inpNumThreads)
        {
            shutdown();

            numThreads = inpNumThreads;
            forceThreadShutdown = false;

            for (int i = 0; i < this.numThreads; ++i)
                lstTh.Add(new Thread(() => threadRoutine(this)));

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
            for (; ; )
            {
                lock (taskPending)
                {
                    if (0 == taskPending.Count)
                    {
                        lock (taskRunning)
                        {
                            while (taskRunning.Count > 0)
                                Monitor.Wait(taskRunning);

                            // no pending task and no running task
                            break;
                        }
                    }
                }
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
            taskRunning.Clear();
        }



        private static void threadRoutine(MyThreadPoolV2B thisPtr)
        {
            ref var taskPending = ref thisPtr.taskPending;
            ref var taskRunning = ref thisPtr.taskRunning;
            IRunnable task = null;

            for (; ; )
            {
                lock (taskPending)
                {
                    // WAIT FOR AN AVAILABLE PENDING TASK
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

                    // PUSH IT TO THE RUNNING QUEUE
                    lock (taskRunning)
                    {
                        taskRunning.Add(task);
                    }
                }

                // DO THE TASK
                task.run();

                // REMOVE IT FROM THE RUNNING QUEUE
                lock (taskRunning)
                {
                    taskRunning.Remove(task);
                    Monitor.PulseAll(taskRunning);
                }
            }
        }
    }
}
