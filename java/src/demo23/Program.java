/*
 * VOLATILE
*/

package demo23;



public class Program {

    public static void main(String[] args) throws InterruptedException {
        new Thread(Program::routine).start();

        Thread.sleep(6000);

        Global.stopped = true;
    }


    private static void routine() {
        while (false == Global.stopped) {
            System.out.println("Running...");
            try { Thread.sleep(2000); } catch (InterruptedException e) { }
        }
    }

}



class Global {
    public static volatile boolean stopped = false;
}
