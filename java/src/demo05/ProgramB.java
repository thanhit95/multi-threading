/*
 * DEMO LIST OF MUTIPLE THREADS
 * Version B: Using stream
*/

package demo05;

import java.util.stream.IntStream;



public class ProgramB {

    public static void main(String[] args) {
        IntStream.range(0, 5).forEach(i -> new Thread(() -> {

            try { Thread.sleep(500); }
            catch (InterruptedException e) { }

            System.out.print(i);

        }).start());
    }

}
