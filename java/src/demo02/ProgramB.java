/*
 * PASSING ARGUMENTS
 * Version B: Passing argument COUNT by capturing it from outside
*/

package demo02;



public class ProgramB {

    public static void main(String[] args) throws InterruptedException {
        final int COUNT = 10;

        new Thread(() -> {
            for (int i = 1; i <= COUNT; ++i)
                System.out.println("Foo " + i);
        }).start();
    }

}
