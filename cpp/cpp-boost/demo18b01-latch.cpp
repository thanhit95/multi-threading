/*
BARRIERS
Version B: Count-down latches
*/


#include <iostream>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/thread/latch.hpp>
using namespace std;



typedef boost::tuple<string,int> tuplestrint;

boost::latch syncPoint(3); // participant count = 3



void processRequest(string userName, int timeWait) {
    boost::this_thread::sleep_for(boost::chrono::seconds(timeWait));

    cout << "Get request from " << userName << endl;

    syncPoint.count_down_and_wait();
    // syncPoint.count_down();
    // syncPoint.wait();

    cout << "Done " << userName << endl;
}



int main() {
    const int NUM_THREADS = 3;
    boost::thread_group lstTh;

    // tuple<userName, timeWait>
    tuplestrint lstArg[NUM_THREADS] = {
        tuplestrint("lorem", 1),
        tuplestrint("ipsum", 2),
        tuplestrint("dolor", 3)
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        tuplestrint & arg = lstArg[i];
        lstTh.add_thread(new boost::thread(
            processRequest, boost::get<0>(arg), boost::get<1>(arg)
        ));
    }

    lstTh.join_all();

    return 0;
}
