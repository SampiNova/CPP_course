#include "./game_objects.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

Universe* read_universe(str name);
void write_universe(const Universe& u, str name);
