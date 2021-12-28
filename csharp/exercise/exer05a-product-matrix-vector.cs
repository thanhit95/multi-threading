/*
 * MATRIX-VECTOR MULTIPLICATION
 */
using System;
using System.Collections.Generic;
using System.Threading;



class Exer05A : IRunnable
{
    public void run()
    {
        double[][] A = new double[][] {
            new double[] { 1, 2, 3 },
            new double[] { 4, 5, 6 },
            new double[] { 7, 8, 9 }
        };

        double[] b = {
            3,
            -1,
            0
        };

        var result = getProduct(A, b);

        Array.ForEach(result, Console.WriteLine);
    }


    private double[] getProduct(double[][] mat, double[] vec)
    {
        // Assume that size of mat and vec are both correct
        int sizeRowMat = mat.Length;
        // int sizeColMat = mat[0].Length;
        // int sizeVec = vec.Length;

        var result = new double[sizeRowMat];
        var lstTh = new List<Thread>();

        for (int ith = 0; ith < sizeRowMat; ++ith)
        {
            int i = ith;

            lstTh.Add(new Thread(() =>
            {
                var u = mat[i];
                var v = vec;
                result[i] = Exer05Util.getScalarProduct(u, v);
            }));
        }

        lstTh.ForEach(th => th.Start());
        lstTh.ForEach(th => th.Join());

        return result;
    }
}
