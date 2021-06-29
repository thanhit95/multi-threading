/*
 * RACE CONDITION AND DATA RACE
*/

package demo12c;



public class Program01 {

    public static void main(String[] args) throws InterruptedException {
        var foo = new MyTask();
        var bar = new MyTask();

        foo.start();
        bar.start();

        foo.join();
        bar.join();

        System.out.println("counter = " + MyTask.counter);
        /*
        We are not sure that counter = 20
        */
    }

}



class MyTask extends Thread {
    static int counter = 0;


    @Override
    public void run() {
        for (int i = 0; i < 10; ++i) {
            try { Thread.sleep(30); }
            catch (InterruptedException e) { }

            counter += 1;
        }
    }
}
