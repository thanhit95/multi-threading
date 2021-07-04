/*
 * CONDITION VARIABLE
*/

package demo21;



public class ProgramC {

    public static void main(String[] args) {
        var conditionVar = new Object();


        Runnable foo = () -> {
            try {
                System.out.println("foo is waiting...");

                synchronized(conditionVar) {
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

            synchronized(conditionVar) {
                conditionVar.notifyAll();
            }
        };


        for (int i = 0; i < 3; ++i)
            new Thread(foo).start();

        new Thread(bar).start();
    }

}
