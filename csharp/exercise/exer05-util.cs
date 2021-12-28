using System;



class Exer05Util
{
    public static double getScalarProduct(double[] u, double[] v)
    {
        double sum = 0;
        int sizeVector = u.Length;

        for (int i = sizeVector - 1; i >= 0; --i)
            sum += u[i] * v[i];

        return sum;
    }


    public static double[][] getTransposeMatrix(double[][] input)
    {
        int numRow = input.Length;
        int numCol = input[0].Length;

        var output = create2dArray<double>(numCol, numRow);

        for (int i = 0; i < numRow; ++i)
            for (int j = 0; j < numCol; ++j)
                output[j][i] = input[i][j];

        return output;
    }


    public static void printMatrix(double[][] mat)
    {
        foreach (var row in mat)
        {
            foreach (var value in row)
                Console.Write($"\t{value:0.0}");

            Console.WriteLine();
        }
    }


    public static T[][] create2dArray<T>(int height, int width)
    {
        T[][] res = new T[height][];

        for (int i = 0; i < height; ++i)
            res[i] = new T[width];

        return res;
    }
}
