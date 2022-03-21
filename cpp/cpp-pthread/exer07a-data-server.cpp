/*
THE DATA SERVER PROBLEM
Version A: Solving the problem using a condition variable
*/


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
using namespace std;



struct Counter {
    int value;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    Counter(int value) : value(value) { }
};



struct ProcessFilesArg {
    const vector<string> * lstFileName;
    Counter * counter;
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
    auto&& counter = *arg->counter;

    for (auto&& fileName : lstFileName) {
        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleep(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        pthread_mutex_lock(&counter.mut);
        {
            --counter.value;
            pthread_cond_signal(&counter.cond);
        }
        pthread_mutex_unlock(&counter.mut);

        // Write log into disk
        sleep(5);
        cout << "[ WriteLog ]" << endl;
    }

    return nullptr;
    pthread_exit(nullptr);
}



void processRequest() {
    const vector<string> lstFileName = { "foo.html", "bar.json" };
    Counter counter(lstFileName.size());

    pthread_t tid;
    ProcessFilesArg arg = { &lstFileName, &counter };

    // The server checks auth user while reading files, concurrently
    pthread_create(&tid, nullptr, &processFiles, &arg);
    checkAuthUser();

    // The server waits for completion of loading files
    pthread_mutex_lock(&counter.mut);
    {
        while (counter.value > 0) {
            pthread_cond_wait(&counter.cond, &counter.mut);
        }
    }
    pthread_mutex_unlock(&counter.mut);

    cout << "\nNow user is authorized and files are loaded" << endl;
    cout << "Do other tasks...\n" << endl;

    pthread_join(tid, nullptr);
    pthread_cond_destroy(&counter.cond);
    pthread_mutex_destroy(&counter.mut);
}



int main() {
    processRequest();
    return 0;
}
