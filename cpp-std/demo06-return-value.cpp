/*
GETTING RETURNED VALUES FROM THREADS
*/

#include <iostream>
#include <thread>

using namespace std;



void worker(int arg, int *res) {
    (*res) = arg * 2;
}



int main() {
    int result[2];

    auto th1 = thread(worker, 5, &result[0]);
    auto th2 = thread(worker, 80, &result[1]);

    th1.join();
    th2.join();

    cout << result[0] << endl;
    cout << result[1] << endl;

    return 0;
}
