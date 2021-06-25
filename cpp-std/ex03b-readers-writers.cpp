/*
THE READERS-WRITERS PROBLEM
Solution for the third readers-writers problem
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <chrono>
#include "mytool-random.hpp"
using namespace std;



using TypeSemaphore = std::counting_semaphore<>;



void funcWriter(
    volatile int* resource,
    TypeSemaphore* semResource,
    TypeSemaphore* semServiceQueue,
    int timeDelay
) {
    std::this_thread::sleep_for(std::chrono::seconds(timeDelay));

    semResource->acquire();

    (*resource) = mytool::RandInt::staticGet() % 100;
    cout << "Write " << (*resource) << endl;

    semResource->release();
}



void funcReader(
    volatile int* resource,
    TypeSemaphore* semResource,
    int* readerCount,
    std::mutex* mutReaderCount,
    TypeSemaphore* semServiceQueue,
    int timeDelay
) {
    std::this_thread::sleep_for(std::chrono::seconds(timeDelay));


    // inrease reader count
    mutReaderCount->lock();
    (*readerCount) += 1;

    if (1 == (*readerCount))
        semResource->acquire();

    mutReaderCount->unlock();


    // do the reading
    int data = (*resource);
    cout << "Read " << data << endl;


    // decrease reader count
    mutReaderCount->lock();
    (*readerCount) -= 1;

    if (0 == (*readerCount))
        semResource->release();

    mutReaderCount->unlock();
}



int main() {
    volatile int resource = 0;

    TypeSemaphore semResource(1);

    int readerCount = 0;
    std::mutex mutReaderCount;

    TypeSemaphore semServiceQueue(1);


    constexpr int NUM_READERS = 8;
    constexpr int NUM_WRITERS = 6;

    std::thread lstThReader[NUM_READERS];
    std::thread lstThWriter[NUM_WRITERS];


    // CREATE THREADS
    for (auto&& th: lstThReader) {
        th = std::thread(
            funcReader,
            &resource, &semResource, &readerCount, &mutReaderCount,
            &semServiceQueue,
            mytool::RandInt::staticGet() % 3
        );
    }

    for (auto&& th: lstThWriter) {
        th = std::thread(
            funcWriter,
            &resource, &semResource,
            &semServiceQueue,
            mytool::RandInt::staticGet() % 3
        );
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
