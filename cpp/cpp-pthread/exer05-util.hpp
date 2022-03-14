#ifndef _EXER05_UTIL_HPP_
#define _EXER05_UTIL_HPP_



struct WorkerScProdArg {
    double const* u = nullptr;
    double const* v = nullptr;
    int sizeVector = 0;
    double* res = nullptr;
};



void* workerScalarProduct(void* argVoid) {
    auto arg = (WorkerScProdArg*) argVoid;
    auto u = arg->u;
    auto v = arg->v;
    auto sizeVector = arg->sizeVector;
    auto res = arg->res;

    double sum = 0;

    for (int i = sizeVector - 1; i >= 0; --i) {
        sum += u[i] * v[i];
    }

    (*res) = sum;

    return nullptr;
}



#endif // _EXER05_UTIL_HPP_
