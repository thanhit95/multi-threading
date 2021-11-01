/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version A02: Using class Thread / Anonymous subclass
*/

package demo01;



public class AppA02 {

    public static void main(String[] args) throws InterruptedException {
        var th1 = new Thread() {
            @Override
            public void run() {
                System.out.println("Hello thread 1");
            }
        };

        var th2 = new Thread() {
            @Override
            public void run() {
                System.out.println("Hello thread 2");
            }
        };

        th1.start();
        th2.start();

        th1.join();
        th2.join();
    }

}
