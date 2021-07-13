/*
THE READERS-WRITERS PROBLEM
Solution for the first readers-writers problem
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <chrono>
#include "mytool-random.hpp"
using namespace std;



using TypeSemaphore = std::counting_semaphore<>;



struct GlobalData {
    volatile int resource = 0;
    TypeSemaphore semResource = TypeSemaphore(1);

    int readerCount = 0;
    std::mutex mutReaderCount;
};



void funcWriter(GlobalData* g, int timeDelay) {
    std::this_thread::sleep_for(std::chrono::seconds(timeDelay));

    g->semResource.acquire();

    g->resource = mytool::RandInt::staticGet() % 100;
    cout << "Write " << g->resource << endl;

    g->semResource.release();
}



void funcReader(GlobalData* g, int timeDelay) {
    std::this_thread::sleep_for(std::chrono::seconds(timeDelay));


    // inrease reader count
    g->mutReaderCount.lock();
    g->readerCount += 1;

    if (1 == g->readerCount)
        g->semResource.acquire();

    g->mutReaderCount.unlock();


    // do the reading
    cout << "Read " << g->resource << endl;


    // decrease reader count
    g->mutReaderCount.lock();
    g->readerCount -= 1;

    if (0 == g->readerCount)
        g->semResource.release();

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
