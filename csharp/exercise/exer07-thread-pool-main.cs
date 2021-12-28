/*
 * THREAD POOL & EXECUTOR SERVICE IMPLEMENTATION
 */
using System;
using System.Collections.Generic;
using System.Threading;



namespace Exer07
{
    class MainApp : IRunnable
    {
        public void run()
        {
            const int NUM_THREADS = 2;
            const int NUM_TASKS = 5;


            var threadPool = new MyThreadPoolV2B();
            threadPool.init(NUM_THREADS);


            var lstTasks = new List<MyTask>();

            for (int i = 0; i < NUM_TASKS; ++i)
                lstTasks.Add(new MyTask((char)('A' + i)));


            lstTasks.ForEach(task => threadPool.submit(task));
            Console.WriteLine("All tasks are submitted");


            threadPool.waitTaskDone();
            Console.WriteLine("All tasks are completed");


            threadPool.shutdown();
        }
    }



    class MyTask : IRunnable
    {
        public char id;

        public MyTask(char id) {
            this.id = id;
        }

        public void run() {
            Console.WriteLine($"Task {id} is starting");
            Thread.Sleep(3000);
            Console.WriteLine($"Task {id} is completed");
        }
    }
}
