#include "game.hpp"
#include <stdexcept>

///////////////////////////////////
//                               //
//    FIELD CLASS REALIZATION    //
//                               //
///////////////////////////////////

Field::Field() {
    this->height = 0;
    this->width = 0;
}
Field::~Field() {}
Field::Field(const Field& f) {
    if (f.get_height() <= 0 || f.get_height() <= 0) {
        throw std::invalid_argument("Input Field is empty");
    }
    this->field = field_type(f.get_height());
    std::copy(f.get_field().begin(), f.get_field().end(), this->field.begin());
    this->width = f.get_width();
    this->height = f.get_height();
}
Field::Field(int width, int height, bool value) {
    if (height < 3 || width < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    row_type tmp(width, value);
    this->field = field_type(height, tmp);
    this->width = width;
    this->height = height;
}

bool Field::empty() const {
    return (this->width <= 0 || this->height <= 0);
}
int Field::get_width() const {
    return this->width;
}
int Field::get_height() const {
    return this->height;
}
field_type Field::get_field() const {
    return this->field;
}

bool Field::at(int row, int col) const {
    if (this->empty()) {
        throw std::runtime_error("This object is empty");
    }
    int i = (row % this->height + this->height) % this->height;
    int j = (col % this->width + this->width) % this->width;
    return this->field[i][j];
}
void Field::set_at(int row, int col, bool value) {
    if (this->empty()) {
        throw std::runtime_error("This object is empty");
    }
    int i = (row % this->height + this->height) % this->height;
    int j = (col % this->width + this->width) % this->width;
    this->field[i][j] = value;
}
void Field::set_field(const field_type& f) {
    if (this->empty()) {
        throw std::runtime_error("This object is empty");
    }
    if (f.size() != this->height)
}

std::ostream& operator<<(std::ostream& out, const Field& f) {
    for (int i = 0; i < f.get_height(); i++) {
        for (int j = 0; j < f.get_width(); j++) {
            if (f.at(i, j)) out << CELL;
            else out << N_CELL;
        }
        out << "\n";
    }
    return out;
}

//////////////////////////////////////
//                                  //
//    UNIVERSE CLASS REALIZATION    //
//                                  //
//////////////////////////////////////

