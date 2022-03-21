/*
THE DATA SERVER PROBLEM
Version A: Solving the problem using a condition variable
*/


#include <iostream>
#include <string>
#include <vector>
#include <boost/ref.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



#define sleepsec(secs) \
    do { boost::this_thread::sleep_for(boost::chrono::seconds(secs)); } while (0)



struct Counter {
    int value;
    boost::mutex mut;
    boost::condition_variable cond;
    Counter(int value) : value(value) { }
};



void checkAuthUser() {
    cout << "[   Auth   ] Start" << endl;
    // Send request to authenticator, check permissions, encrypt, decrypt...
    sleepsec(20);
    cout << "[   Auth   ] Done" << endl;
}



void processFiles(const vector<string>& lstFileName, Counter& counter) {
    for (size_t i = 0; i < lstFileName.size(); ++i) {
        const string& fileName = lstFileName[i];

        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleepsec(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        {
            boost::unique_lock<boost::mutex>(counter.mut);
            --counter.value;
            counter.cond.notify_one();
        }

        // Write log into disk
        sleepsec(5);
        cout << "[ WriteLog ]" << endl;
    }
}



void processRequest() {
    vector<string> lstFileName;
    lstFileName.push_back("foo.html");
    lstFileName.push_back("bar.json");

    Counter counter(lstFileName.size());

    // The server checks auth user while reading files, concurrently
    boost::thread th(&processFiles, boost::cref(lstFileName), boost::ref(counter));
    checkAuthUser();

    // The server waits for completion of loading files
    {
        boost::unique_lock<boost::mutex> lk(counter.mut);
        while (counter.value > 0) {
            counter.cond.wait_for(lk, boost::chrono::seconds(10)); // timeout = 10 seconds
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
