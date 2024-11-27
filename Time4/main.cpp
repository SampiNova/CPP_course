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

	return 0;
}
