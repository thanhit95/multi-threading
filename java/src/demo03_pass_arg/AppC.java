/*
 * PASSING ARGUMENTS
 * Version C: Passing arguments by capturing them
 *
 * Note: The captured variables must be final or effectively final.
 */

package demo03_pass_arg;



public class AppC {

    public static void main(String[] args) throws InterruptedException {
        final int COUNT = 10;

        new Thread(() -> {

            for (int i = 1; i <= COUNT; ++i)
                System.out.println("value: " + i);

        }).start();
    }

}
