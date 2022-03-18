/*
MATRIX-MATRIX MULTIPLICATION (DOT PRODUCT)
*/


#include <iostream>
#include <vector>
#include <pthread.h>
#include "exer05-util.hpp"
using namespace std;



using vectord = std::vector<double>;
using matrix = std::vector<vectord>;



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

    vector<pthread_t> lstTid(sizeTotal);
    vector<WorkerScProdArg> lstArg(sizeTotal);

    int iSca = 0;
    int ret = 0;

    for (int i = 0; i < sizeRowA; ++i) {
        for (int j = 0; j < sizeColB; ++j) {
            auto&& u = matA[i].data();
            auto&& v = matBT[j].data();
            auto&& sizeVector = sizeColA;

            lstArg[iSca] = { u, v, sizeVector, &result[i][j] };

            ret = pthread_create(&lstTid[iSca], nullptr,
                                 &workerScalarProduct, &lstArg[iSca]);

            ++iSca;
        }
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
    }
}



int main() {
    matrix A = {
        { 1, 3, 5 },
        { 2, 4, 6 },
    };

    matrix B = {
        { 1, 0, 1, 0 },
        { 0, 1, 0, 1 },
        { 1, 0, 0, -2 }
    };

    matrix result;
    getProduct(A, B, result);

    displayMatrix(result);

    return 0;
}
