/*
 * MATRIX-MATRIX MULTIPLICATION (DOT PRODUCT)
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer05B : IRunnable
{
    public void run()
    {
        double[][] A = new double[][] {
            new double[] { 1, 3, 5 },
            new double[] { 2, 4, 6 }
        };

        double[][] B = new double[][] {
            new double[] { 1, 0, 1, 0 },
            new double[] { 0, 1, 0, 1 },
            new double[] { 1, 0, 0, -2 }
        };

        double[][] result = getProduct(A, B);

        Exer05Util.printMatrix(result);
    }


    private double[][] getProduct(double[][] matA, double[][] matB)
    {
        // Assume that the size of A and B are both correct
        int sizeRowA = matA.Length;
        int sizeColB = matB[0].Length;

        double[][] matBT = Exer05Util.getTransposeMatrix(matB);
        var result = Exer05Util.create2dArray<double>(sizeRowA, sizeColB);
        var lstTh = new List<Thread>();


        for (int ith = 0; ith < sizeRowA; ++ith)
        {
            int i = ith;

            for (int jth = 0; jth < sizeColB; ++jth)
            {
                int j = jth;
                var u = matA[i];
                var v = matBT[j];

                lstTh.Add(new Thread(() =>
                {
                    result[i][j] = Exer05Util.getScalarProduct(u, v);
                }));
            }
        }


        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());


        return result;
    }
}
