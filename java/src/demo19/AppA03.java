/*
 * SEMAPHORE
 * Version A: Paper and packages
*/

package demo19;

import java.util.concurrent.Semaphore;



public class AppA03 {

    public static void main(String[] args) {
        var semPackage = new Semaphore(0);
        var semPaper = new Semaphore(2);


        Runnable makeOnePaper = () -> {
            for (int i = 0; i < 4; ++i) {
                try {
                    semPaper.acquire();

                    System.out.println("Make 1 paper");

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

                    System.out.println("Combine 2 papers into 1 package");
                    Thread.sleep(1000);

                    semPaper.release(1);
                    // Should be semPaper.release(2). Otherwise, DEADLOCK
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };


        new Thread(makeOnePaper).start();
        new Thread(makeOnePaper).start();
        new Thread(combineOnePackage).start();
    }

}
