/*
 * ASYNCHRONOUS PROGRAMMING WITH THE FUTURE/TASK
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncA04 : IRunnable
{
    public async void run()
    {
        var task = cookEggs();

        // Waiting for task completion
        task.Wait();

        string result = await task;
        Console.WriteLine(result);
    }

    private async Task<string> cookEggs()
    {
        Console.WriteLine("I am cooking eggs");

        // Cooking eggs in 2 seconds
        await Task.Delay(2000);

        /*
         * Avoid using System.Threading.Thread.Sleep(2000)
         * Because one thread can work on multiple tasks at once.
         *
         * Thread.Sleep pauses current thread.
         * Task.Delay pauses current task.
         */

        return "fried eggs";
    }
}
