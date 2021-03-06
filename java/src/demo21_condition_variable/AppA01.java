/*
 * CONDITION VARIABLES
 */

package demo21_condition_variable;



public class AppA01 {

    public static void main(String[] args) {
        var conditionVar = new Object();


        Runnable foo = () -> {
            try {
                System.out.println("foo is waiting...");

                synchronized (conditionVar) {
                    // foo must own the conditionVar before using it
                    conditionVar.wait();
                }

                System.out.println("foo resumed");
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        };


        Runnable bar = () -> {
            try { Thread.sleep(3000); } catch (InterruptedException e) { }

            synchronized (conditionVar) {
                // bar must own the conditionVar before using it
                conditionVar.notify();
            }
        };


        new Thread(foo).start();
        new Thread(bar).start();
    }

}
