#include <iostream>
#include "MainClasses/game.hpp"

#define end '\n'

using namespace std;

int main() {

    Universe uni(10, 10, 0);

    uni.set_cell(0, 1);
    uni.set_cell(1, 2);
    uni.set_cell(2, 0);
    uni.set_cell(2, 1);
    uni.set_cell(2, 2);

    uni.n_ticks(1000, 100);

    return 0;
}
