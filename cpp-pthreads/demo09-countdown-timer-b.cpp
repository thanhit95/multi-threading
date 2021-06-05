#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

using namespace std;



void* userInputFunc(void *argVoid) {
    char buffer[1024] = { 0 };

    cin.getline(buffer, 1024);

    pthread_exit(nullptr);
    return (void*)0;
}



int main() {
    constexpr int SECONDS = 5;

    pthread_t tid;

    timespec ts;

    char buffer[1024] = { 0 };
    int ret;


    cout << "You have " << SECONDS << " seconds to write anything you like in one line." << endl;
    cout << "Press enter to start." << endl;
    cin.getline(buffer, 1024);
    cout << "START!!!" << endl << endl;


    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += SECONDS;


    ret = pthread_create(&tid, nullptr, userInputFunc, nullptr);


    if (ret = pthread_timedjoin_np(tid, nullptr, &ts)) {
        ret = pthread_cancel(tid);  // kill thread
        cout << "\n\nTIMEOUT!!!" << endl;
    }
    else {
        cout << "\nYou completed before the deadline." << endl;
    }

    return 0;
}
