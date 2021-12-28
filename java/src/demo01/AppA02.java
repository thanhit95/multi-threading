/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A02: Using class Thread / Anonymous subclass
*/

package demo01;



public class AppA02 {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread() {
            @Override
            public void run() {
                System.out.println("Hello from Lorem thread");
            }
        };

        th.start();

        System.out.println("Hello from main thread");
    }

}
