/*
 * LIST OF MUTIPLE THREADS
 * Version B02: Using streams (shorten code, no variable to store list of threads)
 */

package demo06;

import java.util.stream.IntStream;



public class AppB02 {

    public static void main(String[] args) {
        IntStream.range(0, 5).forEach(i -> new Thread(() -> {

            try { Thread.sleep(500); }
            catch (InterruptedException e) { }

            System.out.print(i);

        }).start());
    }

}
