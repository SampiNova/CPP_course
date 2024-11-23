#include <iostream>
#include <algorithm>
#include "time/time.hpp"

using namespace std;

int main() {

	Time a(1, 2, 3);

	cout << a << "\n";

	a = Time();

	Time b = a + 178;

	cout << b << "\n";

	cout << "==============\n";

	Time* empty_time = new Time;

	cout << *empty_time << "\n";

	delete empty_time;

	return 0;
}
