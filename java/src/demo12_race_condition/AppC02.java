/*
 * RACE CONDITIONS AND DATA RACES
 */

package demo12_race_condition;



public class AppC02 {

    public static void main(String[] args) throws InterruptedException {
        var thA = new Thread(() -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }

            while (Global.counter < 10)
                ++Global.counter;

            System.out.println("A won !!!");
        });


        var thB = new Thread(() -> {
            try { Thread.sleep(1000); } catch (InterruptedException e) { }

            while (Global.counter > -10)
                --Global.counter;

            System.out.println("B won !!!");
        });


        thA.start();
        thB.start();
    }



    private static class Global {
        public static int counter = 0;
    }

}
