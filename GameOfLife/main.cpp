#include <iostream>
#include <algorithm>
#include "MainClasses/game.hpp"

#define end '\n'

using namespace std;

int main() {

	Field myF(10, 10, 1);

	field2d my_vec(100, 0);
	my_vec[20] = true;

	cout << my_vec[2] << end;

	cout << myF << end;

	Field myF2(my_vec, 10, 10);

	myF2.set_cell(index2d(7, 4), 1);

	myF2.get_field()[65] = 1;

	cout << myF2 << end;

	return 0;
}
