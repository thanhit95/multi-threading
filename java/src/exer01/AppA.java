/*
 * MAXIMUM NUMBER OF DIVISORS
 */

package exer01;

import java.time.Duration;
import java.time.Instant;



public class AppA {

    public static void main(String[] args) {
        final int RANGE_START = 1;
        final int RANGE_END = 100000;

        int resValue = 0;
        int resNumDiv = 0;  // number of divisors of result

        var tpStart = Instant.now();


        for (int i = RANGE_START; i <= RANGE_END; ++i) {
            int numDiv = 0;

            for (int j = i / 2; j > 0; --j)
                if (i % j == 0)
                    ++numDiv;

            if (resNumDiv < numDiv) {
                resNumDiv = numDiv;
                resValue = i;
            }
        }


        var timeElapsed = Duration.between(tpStart, Instant.now());

        System.out.println("The integer which has largest number of divisors is " + resValue);
        System.out.println("The largest number of divisor is " + resNumDiv);
        System.out.println("Time elapsed = " + timeElapsed.toNanos() / 1e9);
    }

}
