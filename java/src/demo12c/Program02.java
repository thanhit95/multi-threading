/*
 * RACE CONDITION AND DATA RACE
*/

package demo12c;



public class Program02 {

    public static void main(String[] args) throws InterruptedException {
        var thA = new TaskCountToWin('A');
        var thB = new TaskCountToWin('B');

        thA.start();
        thB.start();

        thA.join();
        thB.join();
    }

}



class TaskCountToWin extends Thread {
    static int counter = 0;


    char taskType;


    public TaskCountToWin(char taskType) {
        this.taskType = taskType;
    }


    @Override
    public void run() {
        try { Thread.sleep(30); }
        catch (InterruptedException e) { }

        if (taskType == 'A')
            routineA();
        else
            routineB();
    }


    private void routineA() {
        while (counter < 10)
            ++counter;

        System.out.println("A won !!!");
    }


    private void routineB() {
        while (counter < 10)
            ++counter;

        System.out.println("B won !!!");
    }
}
