#include <iostream>
#include <algorithm>
#include "time/time.hpp"
#include "watches/watches.hpp"

using namespace std;

int main() {

	SimpleWatch my_watch(1, 2, 23, true);

	cout << my_watch << "\n";

	my_watch.set_format(false);

	cout << my_watch << "\n";

	SimpleWatch new_watch(4, 5, 16, true);

	my_watch += new_watch;

	cout << my_watch << "\n";

	return 0;
}
