/*
 * THREAD-LOCAL STORAGE
 * Introduction
 *
 * Use valueFactory function for better initialization
 */
using System;
using System.Threading;



class Demo22302 : IRunnable
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
        private static ThreadLocal<string> data = new ThreadLocal<string>(() => "NOT SET");

        public static string get()
        {
            return data.Value;
        }

        public static void set(string value)
        {
            data.Value = value;
        }
    }
}
