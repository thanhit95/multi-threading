/*
MATRIX-MATRIX MULTIPLICATION (DOT PRODUCT)

For an example:

Matrix A:
|   1   3   5   |
|   2   4   6   |

Matrix B:
|   1   0   1   0   |
|   0   1   0   1   |
|   1   0   0   -2  |

The result of dot(A, B) is the matrix:
|   6   3   1   -7  |
|   8   4   2   -8  |

*/


#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;



struct WorkerArg {
    double const *a;
    double const *b;
    int sizeVector;
    double *ptrResult;
};



void* workerDoingScalarProduct(void *argVoid) {
    auto arg = (WorkerArg*)argVoid;
    auto a = arg->a;
    auto b = arg->b;

    double sum = 0;

    for (int i = arg->sizeVector - 1; i >= 0; --i) {
        sum += a[i] * b[i];
    }

    *(arg->ptrResult) = sum;

    pthread_exit(nullptr);
    return (void*)0;
}



typedef vector<double> vectord;
typedef vector<vectord> matrix;



void getTransposeMatrix(const matrix &input, matrix &output) {
    int numRow = input.size();
    int numCol = input[0].size();

    output.clear();
    output.assign(numCol, vectord(numRow, 0));

    for (int i = 0; i < numRow; ++i)
        for (int j = 0; j < numCol; ++j)
            output[j][i] = input[i][j];
}



void displayMatrix(const matrix &mat) {
    int numRow = mat.size();
    int numCol = mat[0].size();

    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < numCol; ++j)
            cout << "\t" << mat[i][j];

        cout << endl;
    }
}



void getProduct(const matrix &matA, const matrix &matB, matrix &result) {
    // assume that the size of A and B are both correct
    int sizeRowA = matA.size();
    int sizeColA = matA[0].size();
    int sizeColB = matB[0].size();
    int sizeTotal = sizeRowA * sizeColB;

    int iSca = 0;
    int ret = 0;

    result.clear();
    result.assign(sizeRowA, vectord(sizeColB, 0));

    matrix matBT;
    getTransposeMatrix(matB, matBT);

    vector<pthread_t> pid(sizeTotal);
    vector<WorkerArg> args(sizeTotal);

    iSca = 0;
    for (int i = 0; i < sizeRowA; ++i) {
        for (int j = 0; j < sizeColB; ++j) {
            args[iSca].a = matA[i].data();
            args[iSca].b = matBT[j].data();
            args[iSca].sizeVector = sizeColA;
            args[iSca].ptrResult = &result[i][j];
            ++iSca;
        }
    }

    iSca = 0;
    for (int i = 0; i < sizeRowA; ++i) {
        for (int j = 0; j < sizeColB; ++j) {
            ret = pthread_create(&pid[iSca], nullptr, workerDoingScalarProduct, &args[iSca]);
            ++iSca;
        }
    }

    for (int i = 0; i < pid.size(); ++i) {
        ret = pthread_join(pid[i], nullptr);
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
