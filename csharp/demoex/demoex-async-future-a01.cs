/*
 * ASYNCHRONOUS PROGRAMMING WITH THE FUTURE/TASK
 */
using System;
using System.Threading.Tasks;
#pragma warning disable CS1998



class DemoExAsyncA01 : IRunnable
{
    public async void run()
    {
        var task = doSomething("cleaning house");

        while (false == task.IsCompleted)
        {
            // Waiting...
        }
    }


    private async Task doSomething(string taskName)

    {
        Console.WriteLine("I am doing " + taskName);
    }
}



#pragma warning restore CS1998
