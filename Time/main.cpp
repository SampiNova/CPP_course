#include "time/time.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <memory>


int main() {
    Time* dynamicTime1 = new Time(10, 20, 30);
    Time* dynamicTimeArray[3];
    dynamicTimeArray[0] = new Time();
    dynamicTimeArray[1] = new Time(1,1,1);
    dynamicTimeArray[2] = new Time(12,34,56);


    std::cout << ">> vector\n";
    std::vector<Time> timeVector;
    timeVector.emplace_back(1,2,3);
    timeVector.emplace_back(4,5,6);

    std::cout << ">> list\n";
    std::list<Time> timeList;
    timeList.emplace_back(7,8,9);
    timeList.emplace_back(10,11,12);


    std::cout << ">> pointers\n";
    auto sharedTime = std::make_shared<Time>(13, 14, 15);
    std::unique_ptr<Time> uniqueTime = std::make_unique<Time>(16,17,18);


    try {
        Time timeWithException(-1, 1, 1);
    } catch (std::runtime_error error) {
        std::cerr << "Exception caught: " << error.what() << std::endl;
    }


    try {
        Time time1(10,20,30);
        time1.set_seconds(-1);
    } catch (std::runtime_error error) {
        std::cerr << "Exception caught: " << error.what() << std::endl;
    }

    Time time2(1,2,3);
    time2 += Time(0,5,10);
    time2 += 1000;
    time2 -= Time(0,1,1);
    time2 -= 60;
    std::cout << "Time2: " << time2.get_hours() << ":" << time2.get_minutes() << ":" << time2.get_seconds() << std::endl;

    Watch watch1(time2);
    watch1.set_format(true);
    std::cout << "Watch format: " << watch1.format() << std::endl;

    delete dynamicTime1;
    for(int i = 0; i < 3; ++i) {
        delete dynamicTimeArray[i];
    }

    return 0;
}


