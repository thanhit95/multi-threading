/*
THE DATA SERVER PROBLEM
Version C: Solving the problem using a count-down latch
*/


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "mylib-latch.hpp"
using namespace std;



struct ProcessFilesArg {
    const vector<string> * lstFileName;
    mylib::CountDownLatch * rdLatch;
};



void checkAuthUser() {
    cout << "[   Auth   ] Start" << endl;
    // Send request to authenticator, check permissions, encrypt, decrypt...
    sleep(20);
    cout << "[   Auth   ] Done" << endl;
}



void* processFiles(void* argVoid) {
    auto arg = (ProcessFilesArg*) argVoid;
    auto&& lstFileName = *arg->lstFileName;
    auto&& rdLatch = *arg->rdLatch;

    for (auto&& fileName : lstFileName) {
        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleep(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        rdLatch.countDown();

        // Write log into disk
        sleep(5);
        cout << "[ WriteLog ]" << endl;
    }

    return nullptr;
    pthread_exit(nullptr);
}



void processRequest() {
    const vector<string> lstFileName = { "foo.html", "bar.json" };
    mylib::CountDownLatch readFileLatch(lstFileName.size());

    pthread_t tid;
    ProcessFilesArg arg = { &lstFileName, &readFileLatch };

    // The server checks auth user while reading files, concurrently
    pthread_create(&tid, nullptr, &processFiles, &arg);
    checkAuthUser();

    // The server waits for completion of loading files
    readFileLatch.wait();

    cout << "\nNow user is authorized and files are loaded" << endl;
    cout << "Do other tasks...\n" << endl;

    pthread_join(tid, nullptr);
}



int main() {
    processRequest();
    return 0;
}
