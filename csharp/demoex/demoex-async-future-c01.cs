/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncC01 : IRunnable
{
    public void run()
    {
        var task = getSquared(7)
            .ContinueWith((previousTask) => getDiv2(previousTask.Result))
            .Unwrap();

        int result = task.Result;
        Console.WriteLine(result);
    }

    private async Task<int> getSquared(int x)
    {
        await Task.Delay(100);
        return x * x;
    }

    private async Task<int> getDiv2(int x)
    {
        await Task.Delay(100);
        return x / 2;
    }
}
