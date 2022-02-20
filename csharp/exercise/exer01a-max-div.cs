/*
 * MAXIMUM NUMBER OF DIVISORS
 */
using System;



class Exer01A : IRunnable
{
    public void run()
    {
        const int RANGE_START = 1;
        const int RANGE_STOP = 100000;

        int resValue = 0;
        int resNumDiv = 0;  // number of divisors of result

        var tpStart = DateTime.Now;


        for (int i = RANGE_START; i <= RANGE_STOP; ++i)
        {
            int numDiv = 0;

            for (int j = i / 2; j > 0; --j)
                if (i % j == 0)
                    ++numDiv;

            if (resNumDiv < numDiv)
            {
                resNumDiv = numDiv;
                resValue = i;
            }
        }


        var timeElapsed = (DateTime.Now - tpStart).TotalSeconds;

        Console.WriteLine("The integer which has largest number of divisors is " + resValue);
        Console.WriteLine("The largest number of divisor is " + resNumDiv);
        Console.WriteLine("Time elapsed = " + timeElapsed);
    }
}
