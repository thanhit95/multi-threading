/*
 * SEMAPHORES
 * Version A: Paper sheets and packages
 */

package demo20;

import java.util.concurrent.Semaphore;



public class AppA03 {

    public static void main(String[] args) {
        var semPackage = new Semaphore(0);
        var semSheet = new Semaphore(2);


        Runnable makeOneSheet = () -> {
            for (int i = 0; i < 4; ++i) {
                try {
                    semSheet.acquire();

                    System.out.println("Make 1 sheet");

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
                    Thread.sleep(1000);

                    semSheet.release(1);
                    // The code causes DEADLOCK due to missing one release.
                    // The code should be semSheet.release(2);
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
