#include <iostream>
#include "MainClasses/game.hpp"

#define end '\n'

using namespace std;

int main() {

    Field myF(20, 10);

    myF.set_at(-1, -1, 1);

    cout << myF << end;

    return 0;
}
