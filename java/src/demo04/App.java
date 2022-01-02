/*
 * SLEEP
 */

package demo04;



public class App {

    public static void main(String[] args) throws InterruptedException {
        var thFoo = new Thread(() -> {
            System.out.println("foo is sleeping");

            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {

            }

            System.out.println("foo wakes up");
        });


        thFoo.start();
        thFoo.join();


        System.out.println("Good bye");
    }

}
