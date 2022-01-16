/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 *
 * The app takes about 3000 miliseconds to run
 * because each method "Task.Wait" pauses app until the task finishes.
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncB02 : IRunnable
{
    public void run()
    {
        var timePointStart = DateTime.Now;

        var taskA = doAction("cooking eggs");
        taskA.Wait();

        var taskB = doAction("making coffee");
        taskB.Wait();

        var taskC = doAction("watching movies");
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
