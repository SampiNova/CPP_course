#include "../include/game_objects.hpp"
#include <stdexcept>

///////////////////////////////////
//                               //
//    FIELD CLASS REALIZATION    //
//                               //
///////////////////////////////////

Field::Field() {
    this->height = 3;
    this->width = 3;
    this->field = field_type(9, false);
}
Field::~Field() {}
Field::Field(const Field& f) {
    this->field = f.get_field();
    this->width = f.get_width();
    this->height = f.get_height();
}
Field::Field(int width, int height, bool value) {
    if (height < 3 || width < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    this->field = field_type(width * height, value);
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
int Field::get_neighbours(int row, int col) const {
    int res = 0;
    if (at(row - 1, col - 1)) res++;
    if (at(row - 1, col)) res++;
    if (at(row - 1, col + 1)) res++;
    if (at(row, col - 1)) res++;
    if (at(row, col + 1)) res++;
    if (at(row + 1, col - 1)) res++;
    if (at(row + 1, col)) res++;
    if (at(row + 1, col + 1)) res++;
    return res;
}
std::vector<std::pair<int, int>> Field::get_points() const {
    std::vector<std::pair<int, int>> res;
    for (int i = 0; i < this->field.size(); i++) {
        if (this->field[i]) {
            int row = i / this->width;
            int col = i % this->width;

            std::pair<int, int> tmp(row, col);
            res.push_back(tmp);
        }
    }
    return res;
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

bool operator==(const Field& f1, const Field& f2) {
    if (f1.get_height() != f2.get_height() || f1.get_width() != f2.get_width()) return false;
    return f1.get_field() == f2.get_field();
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

Universe::Universe(): ticks_cnt(0) {
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
Universe::Universe(const Universe& u): ticks_cnt(0) {
    this->name = u.get_name();
    this->birth = u.get_birth();
    this->survival = u.get_survival();
    this->field = new Field(u.get_field());
}
Universe::Universe(int width, int height, bool value): ticks_cnt(0) {
    if (width < 3 || height < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    this->name = "Unknown";
    this->birth.insert(3);
    this->survival.insert(2);
    this->survival.insert(3);
    this->field = new Field(width, height, value);
}
Universe::Universe(str name, int_set birth, int_set survival, int width, int height, bool value): ticks_cnt(0) {
    if (width < 3 || height < 3) {
        throw std::invalid_argument("Wrong field size");
    }
    this->name = name;
    this->birth = birth;
    this->survival = survival;
    this->field = new Field(width, height, value);
}
Universe::Universe(str name, int_set birth, int_set survival, const Field& f): ticks_cnt(0) {
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
Field& Universe::get_field() const {
    if (!this->field) {
        throw std::runtime_error("Self field is empty.");
    }
    return *this->field;
}
int Universe::get_ticks() const {
    return this->ticks_cnt;
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
void Universe::set_cell_err(int row, int col, bool value) {
    if (!this->field) {
        throw std::runtime_error("Field is empty");
    }
    if (this->field->at(row, col) == value) {
        throw std::invalid_argument("This cell is already setted.");
    }
    this->field->set_at(row, col, value);
}

void Universe::set_ticks(int ticks) {
    if (ticks < 0) {
        throw std::invalid_argument("Ticks must be greater or equal of zero.");
    }
    this->ticks_cnt = ticks;
}

bool Universe::tick() {
    if (!this->field) {
        throw std::runtime_error("Field is empty");
    }
    Field tmp(this->field->get_width(), this->field->get_height());
    for (int i = 0; i < this->field->get_height(); i++) {
        for (int j = 0; j < this->field->get_width(); j++) {
            int cnt = this->field->get_neighbours(i, j);
            if (this->field->at(i, j)) {
                if (this->survival.count(cnt) > 0) {
                    tmp.set_at(i, j, 1);
                }
                else tmp.set_at(i, j, 0);
            }
            else {
                if (this->birth.count(cnt) > 0) {
                    tmp.set_at(i, j, 1);
                }
            }
        }
    }
    this->ticks_cnt++;
    bool res;
    res = (*this->field) == tmp;
    delete this->field;
    this->field = new Field(tmp);
    return res;
}

