/*
 * EXECUTOR SERVICE & THREAD POOL IMPLEMENTATION
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


            var execService = new MyExecServiceV0A(NUM_THREADS);


            var lstTask = new List<MyTask>();

            for (int i = 0; i < NUM_TASKS; ++i)
                lstTask.Add(new MyTask((char)('A' + i)));


            lstTask.ForEach(task => execService.submit(task));
            Console.WriteLine("All tasks are submitted");


            execService.waitTaskDone();
            Console.WriteLine("All tasks are completed");


            execService.shutdown();
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
