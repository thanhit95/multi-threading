/*
 * GETTING THREAD'S ID
 */

package demo05;



public class App {

    public static void main(String[] args) {
        Runnable doTask = () -> {
            long id = Thread.currentThread().getId();
            System.out.println(id);
        };

        var thFoo = new Thread(doTask);
        var thBar = new Thread(doTask);

        System.out.println("foo's id: " + thFoo.getId());
        System.out.println("bar's id: " + thBar.getId());

        thFoo.start();
        thBar.start();
    }

}
