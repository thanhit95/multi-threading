/*
 * GETTING THREAD ID
*/

package demo04;



public class Program {

    public static void main(String[] args) {
        var foo = new Thread(() -> {
            var id = Thread.currentThread().getId();
            System.out.println("Thread id is " + id);
        });

        System.out.println("foo id: " + foo.getId());

        foo.start();
    }

}
