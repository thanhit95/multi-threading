/*
THE DATA SERVER PROBLEM
Version B: Solving the problem using a semaphore
*/


#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <semaphore>
using namespace std;



#define sleepsec(secs) \
    do { std::this_thread::sleep_for(std::chrono::seconds(secs)); } while (0)

using cntsemaphore = std::counting_semaphore<>;



void checkAuthUser() {
    cout << "[   Auth   ] Start" << endl;
    // Send request to authenticator, check permissions, encrypt, decrypt...
    sleepsec(20);
    cout << "[   Auth   ] Done" << endl;
}



void processFiles(const vector<string>& lstFileName, cntsemaphore& sem) {
    for (auto&& fileName : lstFileName) {
        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleepsec(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        sem.release();

        // Write log into disk
        sleepsec(5);
        cout << "[ WriteLog ]" << endl;
    }
}



void processRequest() {
    const vector<string> lstFileName = { "foo.html", "bar.json" };
    cntsemaphore sem(0);

    // The server checks auth user while reading files, concurrently
    std::thread th(&processFiles, std::cref(lstFileName), std::ref(sem));
    checkAuthUser();

    // The server waits for completion of loading files
    for (size_t i = lstFileName.size(); i > 0; --i) {
        sem.acquire();
    }

    cout << "\nNow user is authorized and files are loaded" << endl;
    cout << "Do other tasks...\n" << endl;

    th.join();
}



int main() {
    processRequest();
    return 0;
}
