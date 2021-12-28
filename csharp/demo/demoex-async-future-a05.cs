/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncA05 : IRunnable
{
    public void run()
    {
        var task = cookEggs();

        /*
         * By calling property "Task.Result", app should wait if necessary for the computation to complete
         * and then retrieves its result.
         *
         * So, we can omit the statement "task.Wait()"
         */

        string result = task.Result;
        Console.WriteLine(result);
    }

    private async Task<string> cookEggs()
    {
        Console.WriteLine("I am cooking eggs");

        // Cooking eggs in 2 seconds
        await Task.Delay(2000);

        return "fried eggs";
    }
}
