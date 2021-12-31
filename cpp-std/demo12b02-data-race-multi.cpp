/*
DATA RACES
Version 02: Multithreading
*/


#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
using namespace std;



void markDiv2(vector<bool> & a, int N) {
    for (int i = 2; i <= N; i += 2)
        a[i] = true;
}



void markDiv3(vector<bool> & a, int N) {
    for (int i = 3; i <= N; i += 3)
        a[i] = true;
}



int main() {
    constexpr int N = 8;

    vector<bool> a;
    a.resize(N + 1, false);


    auto thDiv2 = std::thread(markDiv2, std::ref(a), N);
    auto thDiv3 = std::thread(markDiv3, std::ref(a), N);
    thDiv2.join();
    thDiv3.join();


    // result = sum of a (i.e. count numbers of true values in a)
    int result = std::accumulate(a.begin(), a.end(), 0);


    cout << "Number of integers that are divisible by 2 or 3 is: " << result << endl;
    return 0;
}
