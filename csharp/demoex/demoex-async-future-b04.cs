/*
 * ASYNCHRONOUS PROGRAMMING WITH THE FUTURE/TASK
 */
using System;
using System.Threading.Tasks;



class DemoExAsyncB04 : IRunnable
{
    public void run()
    {
        var taskValidation = validate("John");
        bool result = taskValidation.Result;

        if (result)
            Console.WriteLine("User can view movies.");
        else
            Console.WriteLine("Age must be >= 18 to view movies.");
    }


    private async Task<bool> validate(string userName)
    {
        int userAge = await queryUserAge(userName);

        Console.WriteLine("Validating...");

        // Validating in two seconds...
        await Task.Delay(2000);

        return userAge >= 18;
    }


    private async Task<int> queryUserAge(string userName)
    {
        Console.WriteLine("Querying userAge in database...");

        // Querying database in two seconds...
        await Task.Delay(2000);

        if (userName == "Thanh")
            return 26;
        else
            return 17;
    }
}
