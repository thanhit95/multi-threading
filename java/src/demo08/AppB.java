/*
 * GETTING RETURNED VALUES FROM THREADS
 */

package demo08;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        int[] result = new int[2];

        var foo = new Thread(() -> result[0] = doubleValue(5));
        var bar = new Thread(() -> result[1] = doubleValue(80));

        foo.start();
        bar.start();

        // Wait until foo and bar finish
        foo.join();
        bar.join();

        System.out.println(result[0]);
        System.out.println(result[1]);
    }


    private static int doubleValue(int value) {
        return value * 2;
    }

}
