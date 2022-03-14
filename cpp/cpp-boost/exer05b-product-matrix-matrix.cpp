/*
MATRIX-MATRIX MULTIPLICATION (DOT PRODUCT)
*/


#include <iostream>
#include <vector>
#include <boost/assign/std/vector.hpp>
#include <boost/thread.hpp>
#include "exer05-util.hpp"
using namespace std;
using namespace boost::assign;



typedef std::vector<double> vectord;
typedef std::vector<vectord> matrix;



void getTransposeMatrix(const matrix& input, matrix& output) {
    int numRow = input.size();
    int numCol = input[0].size();

    output.clear();
    output.assign(numCol, vectord(numRow, 0));

    for (int i = 0; i < numRow; ++i)
        for (int j = 0; j < numCol; ++j)
            output[j][i] = input[i][j];
}



void displayMatrix(const matrix& mat) {
    int numRow = mat.size();
    int numCol = mat[0].size();

    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < numCol; ++j)
            cout << "\t" << mat[i][j];

        cout << endl;
    }
}



void getProduct(const matrix& matA, const matrix& matB, matrix& result) {
    // Assume that size of matA and matB are both eligible
    int sizeRowA = matA.size();
    int sizeColA = matA[0].size();
    int sizeColB = matB[0].size();
    int sizeTotal = sizeRowA * sizeColB;

    result.clear();
    result.assign(sizeRowA, vectord(sizeColB, 0));

    matrix matBT;
    getTransposeMatrix(matB, matBT);

    boost::thread_group lstTh;

    for (int i = 0; i < sizeRowA; ++i) {
        for (int j = 0; j < sizeColB; ++j) {
            int sizeVector = sizeColA;

            lstTh.add_thread(new boost::thread(
                getScalarProduct, matA[i].data(), matBT[j].data(), sizeVector, &result[i][j]
            ));
        }
    }

    lstTh.join_all();
}



int main() {
    matrix A, B;

    {
        vectord row1, row2;
        row1 += 1, 3, 5;
        row2 += 2, 4, 6;
        A += row1, row2;
    }

    {
        vectord row1, row2, row3;
        row1 += 1, 0, 1, 0;
        row2 += 0, 1, 0, 1;
        row3 += 1, 0, 0, -2;
        B += row1, row2, row3;
    }

    matrix result;
    getProduct(A, B, result);

    displayMatrix(result);

    return 0;
}
