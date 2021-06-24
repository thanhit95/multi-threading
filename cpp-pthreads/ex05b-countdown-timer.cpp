#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
using namespace std;



char *buffer = nullptr;



void* userInputFunc(void *argVoid) {
    cin.getline(buffer, 1024);

    pthread_exit(nullptr);
    return nullptr;
}



int main() {
    constexpr int SECONDS = 5;

    char buff[1024] = { 0 };
    buffer = buff;

    pthread_t tid;
    timespec ts;

    int ret = 0;


    cout << "You have " << SECONDS << " seconds to write anything you like in one line." << endl;
    cout << "Press enter to start." << endl;
    cin.getline(buffer, 1024);
    cout << "START!!!" << endl << endl;


    ret = pthread_create(&tid, nullptr, userInputFunc, nullptr);


    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += SECONDS;


    if (ret = pthread_timedjoin_np(tid, nullptr, &ts)) {
        ret = pthread_cancel(tid);  // kill thread
        cout << "\n\nTIMEOUT!!!" << endl;
    }
    else {
        cout << "\nYou completed before the deadline." << endl;
    }

    return 0;
}
