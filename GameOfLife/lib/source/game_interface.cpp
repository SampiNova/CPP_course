#include "../include/game_interface.hpp"


Interface::Interface() {
    this->uni = nullptr;
}
Interface::~Interface() {
    if (this->uni) {
        delete this->uni;
    }
}
Interface::Interface(const Interface& I) {
    if (this->uni) {
        delete this->uni;
    }
    this->uni = new Universe(I.get_universe());
}
Interface::Interface(const Universe& u) {
    if (this->uni) {
        delete this->uni;
    }
    this->uni = new Universe(u);
}

void Interface::set_universe(const Universe& u) {
    if (this->uni) {
        delete this->uni;
    }
    this->uni = new Universe(u);
}

Universe& Interface::get_universe() const {
    return *this->uni;
}

void Interface::run_cmd(str cmd) const {

}

