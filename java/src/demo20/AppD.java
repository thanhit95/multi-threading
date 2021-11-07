/*
 * CONDITION VARIABLE
*/

package demo20;

public class AppD {

    public static void main(String[] args) {
        new Foo().start();
        new Eggs().start();
    }

}



class Global {
    public static Object conditionVar = new Object();

    public static int counter = 0;

    public static final int COUNT_HALT_01 = 3;
    public static final int COUNT_HALT_02 = 6;
    public static final int COUNT_DONE = 10;
}



// Write numbers 1-3 and 8-10 as permitted by eggs()
class Foo extends Thread {
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
class Eggs extends Thread {
    @Override
    public void run() {
        for (;;) {
            synchronized (Global.conditionVar) {
                if (Global.counter < Global.COUNT_HALT_01 || Global.counter > Global.COUNT_HALT_02) {
                    Global.conditionVar.notify();
                }
                else {
                    Global.counter += 1;
                    System.out.println("eggs counter = " + Global.counter);
                }

                if (Global.counter >= Global.COUNT_DONE) {
                    return;
                }
            }
        }
    }
}
