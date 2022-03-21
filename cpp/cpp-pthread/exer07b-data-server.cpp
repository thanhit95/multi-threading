/*
THE DATA SERVER PROBLEM
Version B: Solving the problem using a semaphore
*/


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <semaphore.h>
using namespace std;



struct ProcessFilesArg {
    const vector<string> * lstFileName;
    sem_t * sem;
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
    auto&& sem = *arg->sem;

    for (auto&& fileName : lstFileName) {
        // Read file
        cout << "[ ReadFile ] Start " << fileName << endl;
        sleep(10);
        cout << "[ ReadFile ] Done  " << fileName << endl;

        sem_post(&sem);

        // Write log into disk
        sleep(5);
        cout << "[ WriteLog ]" << endl;
    }

    return nullptr;
    pthread_exit(nullptr);
}



void processRequest() {
    const vector<string> lstFileName = { "foo.html", "bar.json" };
    sem_t sem;
    sem_init(&sem, 0, 0);

    pthread_t tid;
    ProcessFilesArg arg = { &lstFileName, &sem };

    // The server checks auth user while reading files, concurrently
    pthread_create(&tid, nullptr, &processFiles, &arg);
    checkAuthUser();

    // The server waits for completion of loading files
    for (size_t i = lstFileName.size(); i > 0; --i) {
        sem_wait(&sem);
    }

    cout << "\nNow user is authorized and files are loaded" << endl;
    cout << "Do other tasks...\n" << endl;

    pthread_join(tid, nullptr);
    sem_destroy(&sem);
}



int main() {
    processRequest();
    return 0;
}
