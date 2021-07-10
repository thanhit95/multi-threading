package ex01;

import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;



public class ProgramB {

    public static void main(String[] args) throws InterruptedException {
        final int RANGE_START = 1;
        final int RANGE_STOP = 100000;
        final int NUM_THREADS = 8;


        var lstWorkerArg = prepareArg(RANGE_START, RANGE_STOP, NUM_THREADS);
        var lstWorkerRes = new ArrayList<WorkerResult>();


        var lstTh = lstWorkerArg.stream().map(arg -> new Thread(() -> {

            int resValue = 0;
            int resNumDiv = 0;

            for (int i = arg.iStart; i <= arg.iEnd; ++i) {
                int numDiv = 0;

                for (int j = i / 2; j > 0; --j)
                    if (i % j == 0)
                        ++numDiv;

                if (resNumDiv < numDiv) {
                    resNumDiv = numDiv;
                    resValue = i;
                }
            }

            lstWorkerRes.add(new WorkerResult(resValue, resNumDiv));

        })).toList();


        var tpStart = Instant.now();


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();

        var finalRes = lstWorkerRes.stream().max((lhs, rhs) -> lhs.numDiv - rhs.numDiv).get();


        var timeElapsed = Duration.between(tpStart, Instant.now());


        System.out.println("The integer which has largest number of divisors is " + finalRes.value);
        System.out.println("The largest number of divisor is " + finalRes.numDiv);
        System.out.println("Time elapsed = " + timeElapsed.toNanos() / 1e9);
    }


    private static List<WorkerArg> prepareArg(int rangeStart, int rangeEnd, int numThreads) {
        int rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
        int rangeA = 0, rangeB = 0;

        var lstWorkerArg = new ArrayList<WorkerArg>();

        for (int i = 0; i < numThreads; ++i) {
            rangeA = rangeB;
            rangeB += rangeBlock;

            if (i == numThreads - 1)
                rangeB = rangeEnd - 1;

            lstWorkerArg.add(new WorkerArg(rangeA, rangeB - 1));
        }

        return lstWorkerArg;
    }



    record WorkerArg(int iStart, int iEnd) { }



    record WorkerResult(int value, int numDiv) { }

}
