/*
THE DATA SERVER PROBLEM
Version C: Solving the problem using a count-down latch
*/


#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <latch>
using namespace std;



#define sleepsec(secs) \
    do { std::this_thread::sleep_for(std::chrono::seconds(secs)); } while (0)



void checkAuthUser() {
    cout << "[   Auth   ] Start" << endl;
    // Send request to authenticator, check permissions, encrypt, decrypt...
    sleepsec(20);
    cout << "[   Auth   ] Done" << endl;
}



void processFiles(const vector<string>& lstFileName, std::latch& rdLatch) {
    for (auto&& fileName : lstFileName) {
        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleepsec(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        rdLatch.count_down();

        // Write log into disk
        sleepsec(5);
        cout << "[ WriteLog ]" << endl;
    }
}



void processRequest() {
    const vector<string> lstFileName = { "foo.html", "bar.json" };
    std::latch readFileLatch(lstFileName.size());

    // The server checks auth user while reading files, concurrently
    std::thread th(&processFiles, std::cref(lstFileName), std::ref(readFileLatch));
    checkAuthUser();

    // The server waits for completion of loading files
    readFileLatch.wait();

    cout << "\nNow user is authorized and files are loaded" << endl;
    cout << "Do other tasks...\n" << endl;

    th.join();
}



int main() {
    processRequest();
    return 0;
}
