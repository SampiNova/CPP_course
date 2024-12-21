#include <iostream>
#include "MainClasses/game.hpp"

#define end '\n'

using namespace std;

int main() {

    Universe uni(10, 10, 0);

    cout << uni << "\n";

    uni.set_cell(2, 0);
    uni.set_cell(2, 1);
    uni.set_cell(2, 2);

    cout << uni << "\n";

    return 0;
}
