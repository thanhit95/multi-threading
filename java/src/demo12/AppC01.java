/*
 * RACE CONDITIONS AND DATA RACES
 */

package demo12;



public class AppC01 {

    public static void main(String[] args) throws InterruptedException {
        var thFoo = new WorkerThread();
        var thBar = new WorkerThread();
        var thEgg = new WorkerThread();

        thFoo.start();
        thBar.start();
        thEgg.start();

        thFoo.join();
        thBar.join();
        thEgg.join();

        System.out.println("counter = " + WorkerThread.counter);
        /*
         * We are not sure that counter = 1500
         */
    }

}



class WorkerThread extends Thread {
    static int counter = 0;


    @Override
    public void run() {
        for (int i = 0; i < 500; ++i) {
            try { Thread.sleep(3); }
            catch (InterruptedException e) { }

            counter += 1;
        }
    }
}
