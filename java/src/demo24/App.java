/*
 * THE VOLATILE KEYWORD
 */

package demo24;



public class App {

    public static void main(String[] args) throws InterruptedException {
        Global.isRunning = true;
        new Thread(() -> doTask()).start();

        Thread.sleep(6000);
        Global.isRunning = false;
    }


    private static void doTask() {
        while (Global.isRunning) {
            System.out.println("Running...");
            try { Thread.sleep(2000); } catch (InterruptedException e) { }
        }
    }



    private static class Global {
        public static volatile boolean isRunning;
    }

}
