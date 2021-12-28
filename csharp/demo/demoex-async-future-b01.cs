/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 *
 * The app takes about 1000 miliseconds to run
 * because all 3 tasks are running simultaneously.
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncB01 : IRunnable
{
    public void run()
    {
        var timePointStart = DateTime.Now;

        var taskA = doAction("cooking eggs");
        var taskB = doAction("making coffee");
        var taskC = doAction("watching movies");

        taskA.Wait();
        taskB.Wait();
        taskC.Wait();

        var timePointEnd = DateTime.Now;
        var duration = (timePointEnd - timePointStart).TotalMilliseconds;

        Console.WriteLine($"Total time: {duration} millis");
    }


    private async Task doAction(string actionName)
    {
        Console.WriteLine(actionName);

        // Doing action in one second...
        await Task.Delay(1000);
    }
}
