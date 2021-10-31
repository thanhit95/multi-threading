/*
 * GETTING THREAD'S ID
*/

package demo04;



public class Program {

    public static void main(String[] args) {
        Runnable routine = () -> {
            long id = Thread.currentThread().getId();
            System.out.println(id);
        };

        var foo = new Thread(routine);
        var bar = new Thread(routine);

        System.out.println("foo's id: " + foo.getId());
        System.out.println("bar's id: " + bar.getId());

        foo.start();
        bar.start();
    }

}
