/*
 * THREAD-LOCAL STORAGE
 * Introduction
 */
using System;
using System.Threading;



class Demo23A01 : IRunnable
{
    public void run()
    {
        // Main thread sets value = "APPLE"
        MyTask.set("APPLE");
        Console.WriteLine(MyTask.get());

        // Child thread gets value
        // Expected output: "NOT SET"
        new Thread(() =>
        {
            Console.WriteLine(MyTask.get());
        }).Start();
    }


    class MyTask
    {
        private static ThreadLocal<string> data = new ThreadLocal<string>();

        public static string get()
        {
            if (data.Value is null)
            {
                data.Value = "NOT SET";
            }

            return data.Value;
        }

        public static void set(string value)
        {
            data.Value = value;
        }
    }
}
