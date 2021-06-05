#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;



void* timerFunc(void *argVoid) {
    int seconds = *(int*)argVoid;

    sleep(seconds);

    cout << "\n\nTIMEOUT!!! \n" << endl;

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int SECONDS = 5;

    pthread_t tid;

    char buffer[1024] = { 0 };
    int ret;


    cout << "You have " << SECONDS << " seconds to write anything you like in one line." << endl;
    cout << "Press enter to start." << endl;
    cin.getline(buffer, 1024);
    cout << "START!!!" << endl << endl;


    ret = pthread_create(&tid, nullptr, timerFunc, (void*)&SECONDS);


    cin.getline(buffer, 1024);


    if (ret = pthread_tryjoin_np(tid, nullptr)) {
        ret = pthread_cancel(tid);  // kill thread
        cout << "\nYou completed before the deadline." << endl;
    }

    return 0;
}
