/*
MATRIX-VECTOR MULTIPLICATION
*/


#include <iostream>
#include <vector>
#include <thread>
using namespace std;



using vectord = std::vector<double>;
using matrix = std::vector<vectord>;



void workerScalarProduct(double const *u, double const *v, int sizeVector, double *res) {
    double sum = 0;

    for (int i = sizeVector - 1; i >= 0; --i) {
        sum += u[i] * v[i];
    }

    (*res) = sum;
}



void getProduct(const matrix &mat, const vectord &vec, vectord &result) {
    // Assume that the size of A and b are both correct
    int sizeRowMat = mat.size();
    int sizeColMat = mat[0].size();
    int sizeVec = vec.size();
    int ret = 0;

    result.clear();
    result.resize(sizeRowMat, 0);

    vector<std::thread> lstTh(sizeRowMat);

    for (int i = 0; i < sizeRowMat; ++i) {
        auto&& u = mat[i].data();
        auto&& v = vec.data();
        lstTh[i] = std::thread(workerScalarProduct, u, v, sizeVec, &result[i]);
    }

    for (auto&& th : lstTh) {
        th.join();
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
