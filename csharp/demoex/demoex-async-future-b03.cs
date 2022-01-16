/*
 * ASYNCHRONOUS PROGRAMMING WITH FUTURE/TASK
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncB03 : IRunnable
{
    public void run()
    {
        var taskCookingEggs = cookEggs();
        var taskMakingCoffee = makeCoffee();

        string resultEggs = taskCookingEggs.Result;
        string resultCoffee = taskMakingCoffee.Result;

        Console.WriteLine("Done!");
        Console.WriteLine(resultEggs);
        Console.WriteLine(resultCoffee);
    }


    private async Task<string> cookEggs()
    {
        Console.WriteLine("I am cooking eggs");

        // Cooking eggs in two seconds...
        await Task.Delay(2000);

        return "fried eggs";
    }


    private async Task<string> makeCoffee()
    {
        Console.WriteLine("I am making coffee");

        // Making coffee in four seconds...
        await Task.Delay(4000);

        return "a cup of coffee";
    }
}
