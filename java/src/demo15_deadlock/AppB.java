/*
 * DEADLOCK
 * Version B
 */

package demo15_deadlock;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        final Object resourceA = "resourceA";
        final Object resourceB = "resourceB";


        var thFoo = new Thread(() -> {
            synchronized (resourceA) {
                System.out.println("foo acquired resource A");

                try { Thread.sleep(1000); } catch (InterruptedException e) { }

                synchronized (resourceB) {
                    System.out.println("foo acquired resource B");
                }
            }
        });


        var thBar = new Thread(() -> {
            synchronized (resourceB) {
                System.out.println("bar acquired resource B");

                try { Thread.sleep(1000); } catch (InterruptedException e) { }

                synchronized (resourceA) {
                    System.out.println("bar acquired resource A");
                }
            }
        });


        thFoo.start();
        thBar.start();
        thFoo.join();
        thBar.join();


        System.out.println("You will never see this statement due to deadlock!");
    }

}
