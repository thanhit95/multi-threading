/*
BARRIERS
Version B: Count-down latches

Main thread waits for 3 child threads to get enough data to progress.
*/


#include <iostream>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/thread/latch.hpp>
using namespace std;



typedef boost::tuple<string,int> tuplestrint;

const int NUM_THREADS = 3;
boost::latch syncPoint(NUM_THREADS);



void doTask(string message, int timeWait) {
    boost::this_thread::sleep_for(boost::chrono::seconds(timeWait));

    cout << message << endl;
    syncPoint.count_down();

    boost::this_thread::sleep_for(boost::chrono::seconds(8));
    cout << "Cleanup" << endl;
}



int main() {
    boost::thread_group lstTh;

    // tuple<message, timeWait>
    tuplestrint lstArg[NUM_THREADS] = {
        tuplestrint("Send request to egg.net to get data", 6),
        tuplestrint("Send request to foo.org to get data", 2),
        tuplestrint("Send request to bar.com to get data", 4)
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        tuplestrint & arg = lstArg[i];

        lstTh.add_thread(new boost::thread(
            &doTask, boost::get<0>(arg), boost::get<1>(arg)
        ));
    }

    syncPoint.wait();
    cout << "\nNow we has enough data to progress to next step\n" << endl;

    lstTh.join_all();

    return 0;
}
