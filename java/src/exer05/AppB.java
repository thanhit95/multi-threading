/*
 * MATRIX-MATRIX MULTIPLICATION (DOT PRODUCT)
 */

package exer05;

import java.util.ArrayList;
import java.util.stream.IntStream;



public class AppB {

    public static void main(String[] args) throws InterruptedException {
        double[][] A = {
            { 1, 3, 5 },
            { 2, 4, 6 },
        };

        double[][] B = {
            { 1, 0, 1, 0 },
            { 0, 1, 0, 1 },
            { 1, 0, 0, -2 }
        };

        double[][] result = getProduct(A, B);

        MyUtil.printMatrix(result);
    }


    private static double[][] getProduct(double[][] matA, double[][] matB) throws InterruptedException {
        // Assume that size of matA and matB are both eligible
        int sizeRowA = matA.length;
        int sizeColB = matB[0].length;


        double[][] matBT = MyUtil.getTransposeMatrix(matB);
        var result = new double[sizeRowA][sizeColB];
        var lstTh = new ArrayList<Thread>();


        IntStream.range(0, sizeRowA).forEach(i ->
            IntStream.range(0, sizeColB).forEach(j -> {
                var u = matA[i];
                var v = matBT[j];

                lstTh.add(new Thread(() -> {
                    result[i][j] = MyUtil.getScalarProduct(u, v);
                }));
            })
        );


        for (var th : lstTh)
            th.start();

        for (var th : lstTh)
            th.join();


        return result;
    }

}
