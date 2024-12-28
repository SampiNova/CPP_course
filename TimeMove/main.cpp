#include "time/time.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "--- Move constructor tests ---\n";
    Time t1 = Time(10, 20, 1); 
    Time t2 = std::move(t1);
    std::cout << "t1 after move: " << t1 << "\n";
    std::cout << "t2 after move: " << t2 << "\n";

    Time t3(1, 2, 3);
    Time t4 = std::move(t3);
    std::cout << "t3 after move: " << t3 << "\n";
    std::cout << "t4 after move: " << t4 << "\n";


    std::cout << "\n--- Move assignment operator tests ---\n";
    Time t5;
    t5 = Time(4, 5, 6);
    std::cout << "t5 after move assignment from rvalue: " << t5 << "\n";

    Time t6(7, 8, 9);
    Time t7;
    t7 = std::move(t6);
    std::cout << "t6 after move assignment from lvalue: " << t6 << "\n";
    std::cout << "t7 after move assignment from lvalue: " << t7 << "\n";

    std::cout << "\n--- Vector push_back tests ---\n";
    std::vector<Time> times;

    std::cout << "Pushing rvalue objects:\n";
    times.push_back(Time(10, 11, 12));
    times.push_back(Time(13, 14, 15));

    std::cout << "\nPushing lvalue objects:\n";
    Time t8(1,2,3);
    Time t9(4,5,6);

    times.push_back(std::move(t8));
    times.push_back(std::move(t9));

    std::cout << "\nPushing lvalue with emplace objects:\n";

    times.emplace_back(1, 2, 3);
    times.emplace_back(4, 5, 6);

    std::cout << "\nContent of the vector:\n";
    for (const auto& time : times) {
        std::cout << time << " ";
    }
    std::cout << "\n";

    return 0;
}

