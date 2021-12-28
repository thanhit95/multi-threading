/*
 * RACE CONDITIONS AND DATA RACES
 */

package demo12;



public class AppC01 {

    public static void main(String[] args) throws InterruptedException {
        var foo = new MyTask();
        var bar = new MyTask();
        var egg = new MyTask();

        foo.start();
        bar.start();
        egg.start();

        foo.join();
        bar.join();
        egg.join();

        System.out.println("counter = " + MyTask.counter);
        /*
         * We are not sure that counter = 1500
         */
    }

}



class MyTask extends Thread {
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
