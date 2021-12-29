/*
 * THE VOLATILE KEYWORD
 */

package demo24;



public class App {

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> threadFunc()).start();

        Thread.sleep(6000);

        Global.stopped = true;
    }


    private static void threadFunc() {
        while (false == Global.stopped) {
            System.out.println("Running...");
            try { Thread.sleep(2000); } catch (InterruptedException e) { }
        }
    }



    class Global {
        public static volatile boolean stopped = false;
    }

}
