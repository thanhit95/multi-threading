/*
THE READERS-WRITERS PROBLEM
Solution for the first readers-writers problem
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



struct GlobalData {
    volatile int resource;
    int readerCount;

    boost::mutex mutResource;
    boost::mutex mutReaderCount;
};



void doTaskWriter(GlobalData* g, int timeDelay) {
    boost::this_thread::sleep_for(boost::chrono::seconds(timeDelay));

    g->mutResource.lock();

    g->resource = rand() % 100;
    cout << "Write " << g->resource << endl;

    g->mutResource.unlock();
}



void doTaskReader(GlobalData* g, int timeDelay) {
    boost::this_thread::sleep_for(boost::chrono::seconds(timeDelay));


    // Increase reader count
    g->mutReaderCount.lock();
    g->readerCount += 1;

    if (1 == g->readerCount)
        g->mutResource.lock();

    g->mutReaderCount.unlock();


    // Do the reading
    cout << "Read " << g->resource << endl;


    // Decrease reader count
    g->mutReaderCount.lock();
    g->readerCount -= 1;

    if (0 == g->readerCount)
        g->mutResource.unlock();

    g->mutReaderCount.unlock();
}



int main() {
    srand(time((time_t*)0));


    GlobalData globalData;
    globalData.resource = 0;
    globalData.readerCount = 0;


    const int NUM_READERS = 8;
    const int NUM_WRITERS = 6;

    boost::thread_group lstThReader;
    boost::thread_group lstThWriter;


    // CREATE THREADS
    for (int i = 0; i < NUM_READERS; ++i) {
        lstThReader.add_thread(new boost::thread(
            doTaskReader, &globalData, rand() % 3
        ));
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        lstThWriter.add_thread(new boost::thread(
            doTaskWriter, &globalData, rand() % 3
        ));
    }


    // JOIN THREADS
    lstThReader.join_all();
    lstThWriter.join_all();


    return 0;
}
