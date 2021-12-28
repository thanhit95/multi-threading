/*
 * GETTING RETURNED VALUES FROM THREADS
*/

package demo08;

public class AppB {

    public static void main(String[] args) throws InterruptedException {
        int[] result = new int[2];

        var thFoo = new Thread(() -> result[0] = doubleValue(5));
        var thBar = new Thread(() -> result[1] = doubleValue(80));

        thFoo.start();
        thBar.start();

        // Wait until thFoo and thBar finish
        thFoo.join();
        thBar.join();

        System.out.println(result[0]);
        System.out.println(result[1]);
    }


    private static int doubleValue(int value) {
        return value * 2;
    }

}
