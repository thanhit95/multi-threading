#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;



void funcUserInput(char *buffer, std::condition_variable *cv) {
    cin.getline(buffer, 1024);
    cv->notify_one();
}



/*
Return true if no timeout. Otherwise, return false.
*/
bool waitForTime(const int timeWait, std::condition_variable &cv, std::mutex &mut) {
    std::unique_lock<std::mutex> lk(mut);
    std::cv_status status = cv.wait_for(lk, std::chrono::seconds(timeWait));

    if (std::cv_status::no_timeout == status)
        return true;
    else
        return false;
}



int main() {
    std::condition_variable cv;
    std::mutex mut;

    constexpr int SECONDS = 5;

    char buffer[1024] = { 0 };


    cout << "You have " << SECONDS << " seconds to write anything you like in one line." << endl;
    cout << "Press enter to start." << endl;
    cin.getline(buffer, 1024);
    cout << "START!!!" << endl << endl;


    auto th = std::thread(funcUserInput, buffer, &cv);


    if (waitForTime(SECONDS, cv, mut)) {
        cout << "\nYou completed before the deadline." << endl;
    }
    else {
        cout << "\n\nTIMEOUT!!!" << endl;
    }


    th.join();
    return 0;
}
