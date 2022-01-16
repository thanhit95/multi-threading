/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 */
using System;
using System.Threading.Tasks;
#pragma warning disable CS1998



class DemoExAsyncA02 : IRunnable
{
    public async void run()
    {
        var task = getSquared(7);

        while (false == task.IsCompleted)
        {
            // Waiting...
        }

        int result = await task;
        Console.WriteLine(result);
    }



    private async Task<int> getSquared(int x)

    {
        return x * x;
    }
}



#pragma warning restore CS1998
