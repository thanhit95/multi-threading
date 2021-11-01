/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version extra: Demo thread name and reference to the thread instance executing current thread
*/

package demo01;



public class AppExtra {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread("foo") {
            @Override
            public void run() {
                Thread myself = Thread.currentThread(); // th is myself

                System.out.println("My name is " + this.getName());
                System.out.println("My self is " + myself);
            }
        };

        th.start();

        // Sometimes, Thread.join() is not necessary. Main thread will wait until th finishes.
        // th.join();
    }

}
