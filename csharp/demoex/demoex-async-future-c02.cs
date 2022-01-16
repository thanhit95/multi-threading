/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncC02 : IRunnable
{
    public void run()
    {
        var task = getSquared(7)
            .ContinueWith((previousTask) => getDiv2(previousTask.Result))
            .Unwrap()
            .ContinueWith((previousTask) => Console.WriteLine(previousTask.Result));

        task.Wait();
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
