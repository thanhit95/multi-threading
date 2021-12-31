/*
 * LIST OF MULTIPLE THREADS
 * Version B01: Using streams
 */

package demo06;

import java.util.stream.IntStream;



public class AppB01 {

    public static void main(String[] args) {
        var lstTh = IntStream.range(0, 5).mapToObj(i -> new Thread(() -> {

            try { Thread.sleep(500); }
            catch (InterruptedException e) { }

            System.out.print(i);

        })).toList();


        lstTh.forEach(Thread::start);
        /*
         * for (var th : lstTh)
         *     th.start();
         */
    }

}
