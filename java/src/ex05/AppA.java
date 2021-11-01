/*
 * MATRIX-VECTOR MULTIPLICATION
 */

package ex05;

import java.util.Arrays;
import java.util.stream.IntStream;



public class AppA {

    public static void main(String[] args) throws InterruptedException {
        double[][] A = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        double[] b = {
            3,
            -1,
            0
        };

        var result = getProduct(A, b);

        System.out.println(Arrays.toString(result));
    }


    private static double[] getProduct(double[][] mat, double[] vec) throws InterruptedException {
        // Assume that the size of A and b are both correct
        int sizeRowMat = mat.length;
        // int sizeColMat = mat[0].length;
        // int sizeVec = vec.length;

        var result = new double[sizeRowMat];

        var lstTh = IntStream.range(0, sizeRowMat).mapToObj(i -> new Thread(() -> {
            var u = mat[i];
            var v = vec;
            result[i] = MyUtil.getScalarProduct(u, v);
        })).toList();

        for (Thread th : lstTh)
            th.start();

        for (Thread th : lstTh)
            th.join();

        return result;
    }

}
