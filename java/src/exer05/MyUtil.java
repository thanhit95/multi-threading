package exer05;

import java.text.NumberFormat;



public class MyUtil {

    private static NumberFormat nf;


    static {
        nf = NumberFormat.getInstance();
        nf.setMaximumFractionDigits(1);
    }


    public static double getScalarProduct(double[] u, double[] v) {
        double sum = 0;
        int sizeVector = u.length;

        for (int i = sizeVector - 1; i >= 0; --i) {
            sum += u[i] * v[i];
        }

        return sum;
    }


    public static double[][] getTransposeMatrix(double[][] input) {
        double[][] output = null;

        int numRow = input.length;
        int numCol = input[0].length;

        output = new double[numCol][numRow];

        for (int i = 0; i < numRow; ++i)
            for (int j = 0; j < numCol; ++j)
                output[j][i] = input[i][j];

        return output;
    }


    public static void printMatrix(double[][] mat) {
        for (var row : mat) {
            for (var value : row)
                System.out.print("\t" + nf.format(value));

            System.out.println();
        }
    }

}
