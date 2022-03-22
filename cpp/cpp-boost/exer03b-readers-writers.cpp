/*
THE READERS-WRITERS PROBLEM
Solution for the third readers-writers problem
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "mylib-random.hpp"
using namespace std;



struct GlobalData {
    volatile int resource;
    int readerCount;

    boost::mutex mutResource;
    boost::mutex mutReaderCount;

    boost::mutex mutServiceQueue;
};



void doTaskWriter(GlobalData* g, int delayTime) {
    boost::this_thread::sleep_for(boost::chrono::seconds(delayTime));

    g->mutServiceQueue.lock();

    g->mutResource.lock();

    g->mutServiceQueue.unlock();

    g->resource = mylib::RandInt::get(100);
    cout << "Write " << g->resource << endl;

    g->mutResource.unlock();
}



void doTaskReader(GlobalData* g, int delayTime) {
    boost::this_thread::sleep_for(boost::chrono::seconds(delayTime));


    g->mutServiceQueue.lock();


    // Increase reader count
    g->mutReaderCount.lock();
    g->readerCount += 1;

    if (1 == g->readerCount)
        g->mutResource.lock();

    g->mutReaderCount.unlock();


    g->mutServiceQueue.unlock();


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
            &doTaskReader, &globalData, mylib::RandInt::get(3)
        ));
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        lstThWriter.add_thread(new boost::thread(
            &doTaskWriter, &globalData, mylib::RandInt::get(3)
        ));
    }


    // JOIN THREADS
    lstThReader.join_all();
    lstThWriter.join_all();


    return 0;
}
