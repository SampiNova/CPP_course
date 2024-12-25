#include "./game_objects.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Interface {
private:
    Universe* uni;
public:
    Interface();
    ~Interface();
    Interface(const Interface& I);
    Interface(const Universe& u);

    void set_universe(const Universe& u);

    Universe& get_universe() const;
    
    void run_cmd(str cmd) const;
};


