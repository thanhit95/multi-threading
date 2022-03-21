/*
THE DATA SERVER PROBLEM
Version A: Solving the problem using a condition variable
*/


#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;



#define sleepsec(secs) \
    do { std::this_thread::sleep_for(std::chrono::seconds(secs)); } while (0)



struct Counter {
    int value;
    std::mutex mut;
    std::condition_variable cond;
    Counter(int value) : value(value) { }
};



void checkAuthUser() {
    cout << "[   Auth   ] Start" << endl;
    // Send request to authenticator, check permissions, encrypt, decrypt...
    sleepsec(20);
    cout << "[   Auth   ] Done" << endl;
}



void processFiles(const vector<string>& lstFileName, Counter& counter) {
    for (auto&& fileName : lstFileName) {
        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleepsec(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        {
            std::unique_lock<std::mutex>(counter.mut);
            --counter.value;
            counter.cond.notify_one();
        }

        // Write log into disk
        sleepsec(5);
        cout << "[ WriteLog ]" << endl;
    }
}



void processRequest() {
    const vector<string> lstFileName = { "foo.html", "bar.json" };
    Counter counter(lstFileName.size());

    // The server checks auth user while reading files, concurrently
    std::thread th(&processFiles, std::cref(lstFileName), std::ref(counter));
    checkAuthUser();

    // The server waits for completion of loading files
    {
        std::unique_lock<std::mutex> lk(counter.mut);
        while (counter.value > 0) {
            counter.cond.wait_for(lk, std::chrono::seconds(10)); // timeout = 10 seconds
        }
    }

    cout << "\nNow user is authorized and files are loaded" << endl;
    cout << "Do other tasks...\n" << endl;

    th.join();
}



int main() {
    processRequest();
    return 0;
}
