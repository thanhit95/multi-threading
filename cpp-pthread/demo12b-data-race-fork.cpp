/*
DATA RACE
*/


#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;



int main() {
    int pid = 0;

    pid = fork();

    if (-1 == pid) {
        cerr << "Cannot fork" << endl;
        return 1;
    }


    ofstream ofs;
    ofs.open("tmp-output.txt");

    if (ofs.fail()) {
        return 1;
    }

    cout << "Writing to the file..." << endl;

    ofs << pid << endl;

    ofs.close();
    return 0;
}


/*
The content of the file is UNKNOWN.
It may be:
    0

or
    34

or
    0
    34

or
    34
    0

Assume that 34 and 0 are process ids.
*/
