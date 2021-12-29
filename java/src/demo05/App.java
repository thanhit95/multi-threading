/*
 * GETTING THREAD'S ID
 */

package demo05;



public class App {

    public static void main(String[] args) {
        Runnable threadFunc = () -> {
            long id = Thread.currentThread().getId();
            System.out.println(id);
        };

        var foo = new Thread(threadFunc);
        var bar = new Thread(threadFunc);

        System.out.println("foo's id: " + foo.getId());
        System.out.println("bar's id: " + bar.getId());

        foo.start();
        bar.start();
    }

}
