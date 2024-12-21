#include "game.hpp"
#include <stdexcept>

///////////////////////////////////
//                               //
//    FIELD CLASS REALIZATION    //
//                               //
///////////////////////////////////

Field::Field() {
    this->height = 3;
    this->width = 3;
    this->field = field_type(9, 0);
}
Field::~Field() {}
Field::Field(const Field& f) {
    this->field = field_type(f.get_width() * f.get_height(), 0);
    std::copy(f.get_field().begin(), f.get_field().end(), this->field.begin());
    this->width = f.get_width();
    this->height = f.get_height();
}
Field::Field(int width, int height, bool value) {
    if (height < 3 || width < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    this->field = field_type(width * height, 0);
    this->width = width;
    this->height = height;
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
    int i = (row % this->height + this->height) % this->height;
    int j = (col % this->width + this->width) % this->width;
    return this->field[i * this->width + j];
}
void Field::set_at(int row, int col, bool value) {
    int i = (row % this->height + this->height) % this->height;
    int j = (col % this->width + this->width) % this->width;
    this->field[i * this->width + j] = value;
}
void Field::set_field(const field_type& f) {
    if (f.size() < 3) {
        throw std::invalid_argument("Input vector is too small");
    }
    if (f.size() != this->width * this->height) {
        throw std::invalid_argument("Input vector has wrong size");
    }
    std::copy(f.begin(), f.end(), this->field.begin());
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

Universe::Universe() {
    this->name = "Unknown";
    this->field = nullptr;
    this->birth.insert(3);
    this->survival.insert(2);
    this->survival.insert(3);
}
Universe::~Universe() {
    delete this->field;
    this->field = nullptr;
}
Universe::Universe(const Universe& u) {
    if (this->field) {
        delete this->field;
    }
    this->name = u.get_name();
    this->birth = u.get_birth();
    this->survival = u.get_survival();
    this->field = new Field(u.get_field());
}
Universe::Universe(int width, int height, bool value) {
    if (width < 3 || height < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    this->name = "Unknown";
    this->birth.insert(3);
    this->survival.insert(2);
    this->survival.insert(3);
    this->field = new Field(width, height, value);
}
Universe::Universe(str name, int_set birth, int_set survival, int width, int height, bool value) {
    if (width < 3 || height < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    this->name = name;
    this->birth = birth;
    this->survival = survival;
    this->field = new Field(width, height, value);
}
Universe::Universe(str name, int_set birth, int_set survival, const Field& f) {
    this->name = name;
    this->birth = birth;
    this->survival = survival;
    this->field = new Field(f);
}

str Universe::get_name() const {
    return this->name;
}
int_set Universe::get_birth() const {
    return this->birth;
}
int_set Universe::get_survival() const {
    return this->survival;
}
Field Universe::get_field() const {
    return *this->field;
}

void Universe::set_name(str name) {
    this->name = name;
}
void Universe::set_birth(int_set birth) {
    this->birth = birth;
}
void Universe::set_survival(int_set survival) {
    this->survival = survival;
}
void Universe::set_field(const Field& f) {
    if (this->field) {
        delete this->field;
    }
    this->field = new Field(f);
}
void Universe::set_cell(int row, int col, bool value) {
    if (!this->field) {
        throw std::runtime_error("Field is empty");
    }
    this->field->set_at(row, col, value);
}

int Universe::get_neighbours(int row, int col) const {
    int res = 0;
    if (this->field->at(row - 1, col - 1)) res++;
    if (this->field->at(row - 1, col)) res++;
    if (this->field->at(row - 1, col + 1)) res++;
    if (this->field->at(row, col - 1)) res++;
    if (this->field->at(row, col + 1)) res++;
    if (this->field->at(row + 1, col - 1)) res++;
    if (this->field->at(row + 1, col)) res++;
    if (this->field->at(row + 1, col + 1)) res++;
    return res;
}

void Universe::tick() {
    if (!this->field) {
        throw std::runtime_error("Field is empty");
    }
    Field tmp(this->field->get_width(), this->field->get_height());
    for (int i = 0; i < this->field->get_height(); i++) {
        for (int j = 0; j < this->field->get_width(); j++) {
            if (this->field->at(i, j)) {
                if (this->survival.count(get_neighbours(i, j)) > 0) tmp.set_at(i, j, 1); 
                else tmp.set_at(i, j, 0);
            }
            else {
                if (this->birth.count(get_neighbours(i, j) > 0)) tmp.set_at(i, j, 1); 
            }
        }
    }
    delete this->field;
    this->field = new Field(tmp);
}


std::ostream& operator<<(std::ostream& out, const Universe& u) {
    out << u.get_field();
    return out;
}


