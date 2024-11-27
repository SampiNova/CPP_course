#include <iostream>
#include <algorithm>
#include "CircularBuffer/CircularBuffer.hpp"

using namespace std;

int main() {

	int n = 10;
	CircularBuffer cb(10);

	for (int i = 0; i < 5; i++) {
		cb.push_front(i + 1);
	}

	cout << cb << endl;

	return 0;
}
