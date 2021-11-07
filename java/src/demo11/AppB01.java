/*
 * DATA RACE
 * Version 01: Without multithreading
*/

package demo11;

import java.util.Arrays;



public class AppB01 {

    public static void main(String[] args) {
        final int N = 8;

        int result = getResult(N);

        System.out.println("Numbers of integers that are divisible by 2 or 3 is: " + result);
    }


    static int getResult(int N) {
        var a = new boolean[N + 1];
        Arrays.fill(a, false);

        for (int i = 1; i <= N; ++i)
            if (i % 2 == 0 || i % 3 == 0)
                a[i] = true;

        int res = countTrue(a, N);
        return res;
    }


    static int countTrue(boolean[] a, int N) {
        int count = 0;

        for (int i = 1; i <= N; ++i)
            if (a[i])
                ++count;

        return count;
    }

}
