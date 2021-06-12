/*
MATRIX-VECTOR MULTIPLICATION

For an example:

Matrix A:
|   1   2   3   |
|   4   5   6   |
|   7   8   9   |

Vector b:
|   3   |
|   -1  |
|   0   |

The result of dot(A, b) is the vector:
|   1   |
|   7   |
|   13  |


SOLUTION:
    - Separate matrix A into list of rows.
    - For each row, calculate scalar product with vector b.

    We can process each row individually. Therefore multithreading will get the job done.
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



void getProduct(const matrix &mat, const vectord &vec, vectord &result) {
    // assume that the size of A and b are both correct
    int sizeRowMat = mat.size();
    int sizeColMat = mat[0].size();
    int sizeVec = vec.size();
    int ret = 0;

    result.clear();
    result.resize(sizeRowMat, 0);

    vector<pthread_t> pid(sizeRowMat);
    vector<WorkerArg> args(sizeRowMat);

    for (int i = 0; i < args.size(); ++i) {
        args[i].a = mat[i].data();
        args[i].b = vec.data();
        args[i].sizeVector = sizeVec;
        args[i].ptrResult = &result[i];
    }

    for (int i = 0; i < sizeRowMat; ++i) {
        ret = pthread_create(&pid[i], nullptr, workerDoingScalarProduct, (void*)&args[i]);
    }

    for (int i = 0; i < sizeRowMat; ++i) {
        ret = pthread_join(pid[i], nullptr);
    }
}



int main() {
    matrix A = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    vectord b = {
        3,
        -1,
        0
    };

    vectord result;
    getProduct(A, b, result);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }

    return 0;
}
