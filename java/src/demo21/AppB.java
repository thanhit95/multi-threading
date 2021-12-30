/*
 * CONDITION VARIABLES
 */

package demo21;



public class AppB {

    public static void main(String[] args) {
        new FooThread().start();
        new EggThread().start();
    }

}



class Global {
    public static Object conditionVar = new Object();

    public static int counter = 0;

    public static final int COUNT_HALT_01 = 3;
    public static final int COUNT_HALT_02 = 6;
    public static final int COUNT_DONE = 10;
}



// Write numbers 1-3 and 8-10 as permitted by egg()
class FooThread extends Thread {
    @Override
    public void run() {
        for (;;) {
            synchronized (Global.conditionVar) {
                try {
                    Global.conditionVar.wait();

                    Global.counter += 1;
                    System.out.println("foo counter = " + Global.counter);

                    if (Global.counter >= Global.COUNT_DONE) {
                        return;
                    }
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}



// Write numbers 4-7
class EggThread extends Thread {
    @Override
    public void run() {
        for (;;) {
            synchronized (Global.conditionVar) {
                if (Global.counter < Global.COUNT_HALT_01 || Global.counter > Global.COUNT_HALT_02) {
                    Global.conditionVar.notify();
                }
                else {
                    Global.counter += 1;
                    System.out.println("egg counter = " + Global.counter);
                }

                if (Global.counter >= Global.COUNT_DONE) {
                    return;
                }
            }
        }
    }
}
