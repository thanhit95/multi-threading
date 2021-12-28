/*
 * SEMAPHORES
 * Version A: Paper sheets and packages
 */

package demo20;

import java.util.concurrent.Semaphore;



public class AppA01 {

    public static void main(String[] args) {
        var semPackage = new Semaphore(0);


        Runnable makeOneSheet = () -> {
            for (int i = 0; i < 4; ++i) {
                try {
                    System.out.println("Make 1 sheet");
                    Thread.sleep(1000);

                    semPackage.release();
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };


        Runnable combineOnePackage = () -> {
            for (int i = 0; i < 4; ++i) {
                try {
                    semPackage.acquire(2);
                    System.out.println("Combine 2 sheets into 1 package");
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };


        new Thread(makeOneSheet).start();
        new Thread(makeOneSheet).start();
        new Thread(combineOnePackage).start();
    }

}
