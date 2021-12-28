/*
 * CONDITION VARIABLES
 */
using System;
using System.Threading;



class Demo21B : IRunnable
{
    public void run()
    {
        new Thread(foo).Start();
        new Thread(egg).Start();
    }


    private void foo()
    {
        for (; ; )
        {
            lock (Global.conditionVar)
            {
                Monitor.Wait(Global.conditionVar);

                Global.counter += 1;
                Console.WriteLine("foo counter = " + Global.counter);

                if (Global.counter >= Global.COUNT_DONE)
                {
                    return;
                }
            }
        }
    }


    private void egg()
    {
        for (; ; )
        {
            lock (Global.conditionVar)
            {
                if (Global.counter < Global.COUNT_HALT_01 || Global.counter > Global.COUNT_HALT_02)
                {
                    Monitor.Pulse(Global.conditionVar);
                }
                else
                {
                    Global.counter += 1;
                    Console.WriteLine("egg counter = " + Global.counter);
                }

                if (Global.counter >= Global.COUNT_DONE)
                {
                    return;
                }
            }
        }
    }


    private class Global
    {
        public static object conditionVar = new object();

        public static int counter = 0;

        public const int COUNT_HALT_01 = 3;
        public const int COUNT_HALT_02 = 6;
        public const int COUNT_DONE = 10;
    }
}
