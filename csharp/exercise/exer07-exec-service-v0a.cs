/*
 * MY EXECUTOR SERVICE
 *
 * Version 0A: The easiest executor service
 * - It uses a blocking queue as underlying mechanism.
 */
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;



namespace Exer07
{
    class MyExecServiceV0A
    {
        private int numThreads = 0;
        private List<Thread> lstTh = new List<Thread>();
        private BlockingCollection<IRunnable> taskPending = new BlockingCollection<IRunnable>();



        public MyExecServiceV0A(int numThreads) {
            init(numThreads);
        }



        private void init(int inpNumThreads)
        {
            numThreads = inpNumThreads;

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
            // so there is no implementation for waitTaskDone()
            Thread.Sleep(11000); // fake behaviour
        }



        public void shutdown()
        {
            // This ExecService is too simple,
            // so there is no implementation for shutdown()
            Console.WriteLine("No implementation for shutdown().");
            Console.WriteLine("You need to exit the app manually.");
        }



        private static void threadWorkerFunc(MyExecServiceV0A thisPtr)
        {
            ref var taskPending = ref thisPtr.taskPending;
            IRunnable task = null;

            for (; ; )
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                task = taskPending.Take();

                // DO THE TASK
                task.run();
            }
        }
    }
}
