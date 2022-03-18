/*
 * MAXIMUM NUMBER OF DIVISORS
 */

package exer01;

import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        final int RANGE_START = 1;
        final int RANGE_END = 100000;
        final int NUM_THREADS = 8;


        var lstWorkerArg = prepareArg(RANGE_START, RANGE_END, NUM_THREADS);
        final var lstWorkerRes = new ArrayList<WorkerResult>();


        var lstWorker = lstWorkerArg.stream().map(arg -> new Thread(() -> {

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

            synchronized (lstWorkerRes) {
                lstWorkerRes.add(new WorkerResult(resValue, resNumDiv));
            }

        })).toList();


        var tpStart = Instant.now();

        for (var worker : lstWorker)
            worker.start();

        for (var worker : lstWorker)
            worker.join();

        var finalRes = lstWorkerRes.stream().max((lhs, rhs) -> lhs.numDiv - rhs.numDiv).get();

        var timeElapsed = Duration.between(tpStart, Instant.now());


        System.out.println("The integer which has largest number of divisors is " + finalRes.value);
        System.out.println("The largest number of divisor is " + finalRes.numDiv);
        System.out.println("Time elapsed = " + timeElapsed.toNanos() / 1e9);


        /*
         * BETTER WAY (avoiding synchronization of lstWorkerRes):
         *
         * - Initialize lstWorkerRes with null objects.
         *   Of course, the number of objects is NUM_THREADS.
         *
         * - In thread function:
         *   lstWorkerRes.set(threadIndex, new WorkerResult(resValue, resNumDiv));
         */
    }


    private static List<WorkerArg> prepareArg(int rangeStart, int rangeEnd, int numThreads) {
        int rangeA, rangeB, rangeBlock;

        rangeBlock = (rangeEnd - rangeStart + 1) / numThreads;
        rangeA = rangeStart;

        var lstWorkerArg = new ArrayList<WorkerArg>();

        for (int i = 0; i < numThreads; ++i, rangeA += rangeBlock) {
            rangeB = rangeA + rangeBlock - 1;

            if (i == numThreads - 1)
                rangeB = rangeEnd;

            lstWorkerArg.add(new WorkerArg(rangeA, rangeB));
        }

        return lstWorkerArg;
    }



    private record WorkerArg(int iStart, int iEnd) { }



    private record WorkerResult(int value, int numDiv) { }

}
