/*
 * DATA RACE
 * Version 02: Multithreading
*/

package demo12;

import java.util.Arrays;



public class AppB02 {

    public static void main(String[] args) throws InterruptedException {
        final int N = 8;


        var a = new boolean[N + 1];
        Arrays.fill(a, false);


        var thDiv2 = new Thread(() -> {
            for (int i = 2; i <= N; i += 2)
                a[i] = true;
        });

        var thDiv3 = new Thread(() -> {
            for (int i = 3; i <= N; i += 3)
                a[i] = true;
        });


        thDiv2.start();
        thDiv3.start();
        thDiv2.join();
        thDiv3.join();


        int result = countTrue(a, N);
        System.out.println("Numbers of integers that are divisible by 2 or 3 is: " + result);
    }


    static int countTrue(boolean[] a, int N) {
        int count = 0;

        for (int i = 1; i <= N; ++i)
            if (a[i])
                ++count;

        return count;
    }

}
