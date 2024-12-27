#include "./game_objects.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

/**
* @brief Reading universe from file
*
* @param Path to reading file
* @return Returns pointer at new Universe from file
*/
Universe* read_universe(str name);
/**
* @brief Writing Universe in file
*
* @param Universe object and path to file
*/
void write_universe(const Universe& u, str name);
