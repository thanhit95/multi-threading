/*
 * INTRODUCTION TO MULTITHREADING
 * You should try running this app several times and see results.
*/

package demo00;



public class App {

    public static void main(String[] args) {
        Thread th = new LoremClass();

        th.start();

        for (int i = 0; i < 300; ++i)
            System.out.print("A");
    }

}



class LoremClass extends Thread {
    @Override
    public void run() {
        for (int i = 0; i < 300; ++i)
            System.out.print("B");
    }
}
