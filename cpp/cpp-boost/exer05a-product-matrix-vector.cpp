/*
MATRIX-VECTOR MULTIPLICATION
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



void getProduct(const matrix& mat, const vectord& vec, vectord& result) {
    // Assume that size of mat and vec are both eligible
    int sizeRowMat = mat.size();
    int sizeColMat = mat[0].size();
    int sizeVec = vec.size();

    result.clear();
    result.resize(sizeRowMat, 0);

    boost::thread_group lstTh;

    for (int i = 0; i < sizeRowMat; ++i) {
        lstTh.add_thread(new boost::thread(
            &getScalarProduct, mat[i].data(), vec.data(), sizeVec, &result[i]
        ));
    }

    lstTh.join_all();
}



int main() {
    matrix A;

    {
        vectord row1, row2, row3;
        row1 += 1, 2, 3;
        row2 += 4, 5, 6;
        row3 += 7, 8, 9;
        A += row1, row2, row3;
    }

    vectord b;
    b += 3, -1, 0;

    vectord result;
    getProduct(A, b, result);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }

    return 0;
}
