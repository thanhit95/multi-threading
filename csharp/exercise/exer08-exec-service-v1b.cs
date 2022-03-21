/*
 * MY EXECUTOR SERVICE
 *
 * Version 1B: Simple executor service
 * - Method "waitTaskDone" uses a condition variable to synchronize.
 */
using System;
using System.Collections.Generic;
using System.Threading;



namespace Exer08
{
    class MyExecServiceV1B
    {
        private int numThreads = 0;
        private List<Thread> lstTh = new List<Thread>();

        private Queue<IRunnable> taskPending = new Queue<IRunnable>();

        private int counterTaskRunning = 0;
        private object lkTaskRunning = new object();

        private volatile bool forceThreadShutdown = false;



        public MyExecServiceV1B(int numThreads) {
            init(numThreads);
        }



        private void init(int inpNumThreads)
        {
            // shutdown();

            numThreads = inpNumThreads;
            counterTaskRunning = 0;
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
            for (; ; )
            {
                lock (taskPending)
                {
                    if (0 == taskPending.Count)
                    {
                        lock (lkTaskRunning)
                        {
                            while (counterTaskRunning > 0)
                            {
                                Monitor.Wait(lkTaskRunning);
                            }

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
        }



        private static void threadWorkerFunc(MyExecServiceV1B thisPtr)
        {
            ref var taskPending = ref thisPtr.taskPending;
            ref var counterTaskRunning = ref thisPtr.counterTaskRunning;
            ref var lkTaskRunning = ref thisPtr.lkTaskRunning;

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

                    ++counterTaskRunning;
                }

                // DO THE TASK
                task.run();

                lock (lkTaskRunning)
                {
                    --counterTaskRunning;

                    if (0 == counterTaskRunning) {
                        Monitor.Pulse(lkTaskRunning);
                    }
                }
            }
        }
    }
}
