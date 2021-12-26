/*
MATRIX-VECTOR MULTIPLICATION
*/


#include <iostream>
#include <vector>
#include <pthread.h>
using namespace std;



using vectord = std::vector<double>;
using matrix = std::vector<vectord>;



struct WorkerArg {
    double const* u = nullptr;
    double const* v = nullptr;
    int sizeVector = 0;
    double* res = nullptr;
};



void* workerScalarProduct(void* argVoid) {
    auto arg = (WorkerArg*)argVoid;
    auto u = arg->u;
    auto v = arg->v;
    auto sizeVector = arg->sizeVector;
    auto res = arg->res;

    double sum = 0;

    for (int i = sizeVector - 1; i >= 0; --i) {
        sum += u[i] * v[i];
    }

    (*res) = sum;

    pthread_exit(nullptr);
    return nullptr;
}



void getProduct(const matrix& mat, const vectord& vec, vectord& result) {
    // Assume that size of mat and vec are both eligible
    int sizeRowMat = mat.size();
    int sizeColMat = mat[0].size();
    int sizeVec = vec.size();
    int ret = 0;

    result.clear();
    result.resize(sizeRowMat, 0);

    vector<pthread_t> lstTid(sizeRowMat);
    vector<WorkerArg> arg(sizeRowMat);

    for (int i = 0; i < sizeRowMat; ++i) {
        auto&& u = mat[i].data();
        auto&& v = vec.data();
        arg[i] = { u, v, sizeVec, &result[i] };

        ret = pthread_create(&lstTid[i], nullptr, workerScalarProduct, &arg[i]);
    }

    for (auto&& tid : lstTid) {
        ret = pthread_join(tid, nullptr);
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
