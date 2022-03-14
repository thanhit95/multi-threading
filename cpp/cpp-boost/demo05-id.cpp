/*
GETTING THREAD'S ID
*/


#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
using namespace std;



void doTask() {
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    cout << boost::this_thread::get_id() << endl;
}



int main() {
    boost::thread thFoo(doTask);
    boost::thread thBar(doTask);

    cout << "foo's id: " << thFoo.get_id() << endl;
    cout << "bar's id: " << thBar.get_id() << endl;

    thFoo.join();
    thBar.join();

    return 0;
}
