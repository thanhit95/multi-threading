/*
 * HELLO WORLD VERSION MULTITHREADING
 * Version extra: Getting thread name and reference to thread instance executing current thread
 */

package demo01;



public class AppExtra {

    public static void main(String[] args) throws InterruptedException {
        var th = new Thread("Lorem") {
            @Override
            public void run() {
                Thread myself = Thread.currentThread(); // th is myself

                System.out.println("My name is " + this.getName()); // or myself.getName()
                System.out.println("My self is " + myself);
            }
        };

        th.start();
    }

}
