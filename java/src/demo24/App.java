/*
 * THE VOLATILE KEYWORD
 */

package demo24;



public class App {

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> doTask()).start();

        Thread.sleep(6000);

        Global.stopped = true;
    }


    private static void doTask() {
        while (false == Global.stopped) {
            System.out.println("Running...");
            try { Thread.sleep(2000); } catch (InterruptedException e) { }
        }
    }



    private static class Global {
        public static volatile boolean stopped = false;
    }

}
