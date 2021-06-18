#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "mytool-time.hpp"
using namespace std;



void writeToFile(string fileName, string programName) {
    ofstream ofs;
    ofs.open(fileName, ios::app);

    if (ofs.fail()) {
        return;
    }

    ofs << programName << endl;
    ofs.close();
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please run program with 2 arguments to specify:" << endl;
        cerr << "\tArgument 1: Waiting seconds (positive integer)" << endl;
        cerr << "\tArgument 2: Program name (string)" << endl;
        return 1;
    }


    const string fileName = "tmp-output.txt";
    const int waitingSeconds = std::stoi(argv[1]);
    const string programName = string(argv[2]);


    cout << "This program name is " << programName << endl;
    cout << "Please run this program twice to achieve 'data race'" << endl;


    auto tpFutureWakeUp = mytool::getTimePointFutureFloor(
        std::chrono::system_clock::now(),
        waitingSeconds
    );


    cout << "Program will sleep until " << mytool::getTimePointStr(tpFutureWakeUp) << endl;


    std::this_thread::sleep_until(tpFutureWakeUp);


    cout << "Writing to the file " << fileName << "..." << endl;
    writeToFile(fileName, programName);


    return 0;
}
