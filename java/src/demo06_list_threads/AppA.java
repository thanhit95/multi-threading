/*
 * LIST OF MULTIPLE THREADS
 * Version A: Using java.util.List / java.util.ArrayList
 */

package demo06_list_threads;

import java.util.ArrayList;



public class AppA {

    public static void main(String[] args) {
        final int NUM_THREADS = 5;

        var lstTh = new ArrayList<Thread>();


        for (int i = 0; i < NUM_THREADS; ++i) {
            final int index = i;

            lstTh.add(new Thread(() -> {
                try { Thread.sleep(500); }
                catch (InterruptedException e) { }

                System.out.print(index);
            }));
        }


        for (var th : lstTh)
            th.start();

        // We can reduce above for loop with this statement:
        // lstTh.forEach(Thread::start);
    }

}
