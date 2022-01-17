/*
COUNTDOWN TIMER
*/


#include <iostream>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
using namespace std;



char* buffer = nullptr;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;



void* funcUserInput(void*) {
    cin.getline(buffer, 1024);
    pthread_cond_signal(&cond);

    pthread_exit(nullptr);
    return nullptr;
}



/*
Return true if no timeout. Otherwise, return false.
*/
bool waitForTime(const int timeWait) {
    int ret = 0;

    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeWait;

    pthread_mutex_lock(&mut);

    ret = pthread_cond_timedwait(&cond, &mut, &ts);

    pthread_mutex_unlock(&mut);

    if (0 != ret) {
        // if (ETIMEDOUT == ret) return false;
        return false;
    }

    return true;
}



int main() {
    constexpr int SECONDS = 5;

    char buff[1024] = { 0 };
    buffer = buff;

    pthread_t tid;
    int ret = 0;


    cout << "You have " << SECONDS << " seconds to write anything you like in one line." << endl;
    cout << "Press enter to start." << endl;
    cin.getline(buffer, 1024);
    cout << "START!!!" << endl << endl;


    ret = pthread_create(&tid, nullptr, funcUserInput, nullptr);


    if (waitForTime(SECONDS)) {
        cout << "\nYou completed before the deadline." << endl;
    }
    else {
        ret = pthread_cancel(tid);  // Kill thread
        cout << "\n\nTIMEOUT!!!" << endl;
    }


    ret = pthread_join(tid, nullptr);


    ret = pthread_mutex_destroy(&mut);
    ret = pthread_cond_destroy(&cond);

    return 0;
}
