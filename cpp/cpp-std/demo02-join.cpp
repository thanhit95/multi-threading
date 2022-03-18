/*
THREAD JOINS
*/


#include <iostream>
#include <thread>
using namespace std;



void doHeavyTask() {
    // Do a heavy task, which takes a little time
    for (int i = 0; i < 2000000000; ++i);

    cout << "Done!" << endl;
}



int main() {
    std::thread th(&doHeavyTask);

    th.join();

    cout << "Good bye!" << endl;

    return 0;
}
