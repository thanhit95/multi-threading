/*
DATA RACES
Version 02: Multithreading
*/


#include <iostream>
#include <vector>
#include <numeric>
#include <boost/ref.hpp>
#include <boost/thread.hpp>
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
    const int N = 8;

    vector<bool> a;
    a.resize(N + 1, false);

    boost::thread thDiv2(&markDiv2, boost::ref(a), N);
    boost::thread thDiv3(&markDiv3, boost::ref(a), N);
    thDiv2.join();
    thDiv3.join();

    // result = sum of a (i.e. counting numbers of true values in a)
    int result = std::accumulate(a.begin(), a.end(), 0);

    cout << "Number of integers that are divisible by 2 or 3 is: " << result << endl;
    return 0;
}
