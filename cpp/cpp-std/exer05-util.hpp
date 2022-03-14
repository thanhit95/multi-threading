#ifndef _EXER05_UTIL_HPP_
#define _EXER05_UTIL_HPP_



void getScalarProduct(double const* u, double const* v, int sizeVector, double* res) {
    double sum = 0;

    for (int i = sizeVector - 1; i >= 0; --i) {
        sum += u[i] * v[i];
    }

    (*res) = sum;
}



#endif // _EXER05_UTIL_HPP_
