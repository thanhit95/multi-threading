/*
 * DEADLOCK
 * Version B
 */

package demo15;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        final Object resourceA = "resourceA";
        final Object resourceB = "resourceB";


        var foo = new Thread(() -> {
            synchronized (resourceA) {
                System.out.println("foo entered resource A");

                try { Thread.sleep(1000); } catch (InterruptedException e) { }

                synchronized (resourceB) {
                    System.out.println("foo entered resource B");
                }
            }
        });


        var bar = new Thread(() -> {
            synchronized (resourceB) {
                System.out.println("bar entered resource B");

                try { Thread.sleep(1000); } catch (InterruptedException e) { }

                synchronized (resourceA) {
                    System.out.println("bar entered resource A");
                }
            }
        });


        foo.start();
        bar.start();


        foo.join();
        bar.join();


        System.out.println("You will never see this statement due to deadlock!");
    }

}
