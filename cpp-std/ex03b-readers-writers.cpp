/*
THE READERS-WRITERS PROBLEM
Solution for the third readers-writers problem
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "mytool-random.hpp"
using namespace std;



struct GlobalData {
    volatile int resource = 0;
    int readerCount = 0;

    std::mutex mutResource;
    std::mutex mutReaderCount;

    std::mutex mutServiceQueue;
};



void funcWriter(GlobalData* g, int timeDelay) {
    std::this_thread::sleep_for(std::chrono::seconds(timeDelay));

    g->mutServiceQueue.lock();

    g->mutResource.lock();

    g->mutServiceQueue.unlock();

    g->resource = mytool::RandInt::staticGet() % 100;
    cout << "Write " << g->resource << endl;

    g->mutResource.unlock();
}



void funcReader(GlobalData* g, int timeDelay) {
    std::this_thread::sleep_for(std::chrono::seconds(timeDelay));


    g->mutServiceQueue.lock();


    // inrease reader count
    g->mutReaderCount.lock();
    g->readerCount += 1;

    if (1 == g->readerCount)
        g->mutResource.lock();

    g->mutReaderCount.unlock();


    g->mutServiceQueue.unlock();


    // do the reading
    cout << "Read " << g->resource << endl;


    // decrease reader count
    g->mutReaderCount.lock();
    g->readerCount -= 1;

    if (0 == g->readerCount)
        g->mutResource.unlock();

    g->mutReaderCount.unlock();
}



int main() {
    GlobalData globalData;


    constexpr int NUM_READERS = 8;
    constexpr int NUM_WRITERS = 6;

    std::thread lstThReader[NUM_READERS];
    std::thread lstThWriter[NUM_WRITERS];


    // CREATE THREADS
    for (auto&& th: lstThReader) {
        th = std::thread(funcReader, &globalData, mytool::RandInt::staticGet() % 3);
    }

    for (auto&& th: lstThWriter) {
        th = std::thread(funcWriter, &globalData, mytool::RandInt::staticGet() % 3);
    }


    // JOIN THREADS
    for (auto&& th: lstThReader) {
        th.join();
    }

    for (auto&& th: lstThWriter) {
        th.join();
    }


    return 0;
}
