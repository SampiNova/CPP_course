#include "game.hpp"

///////////////////////////////////
//                               //
//    FIELD CLASS REALISATION    //
//                               //
///////////////////////////////////

Field::Field() noexcept {
	this->width = 0;
	this->height = 0;
}

Field::~Field() {

}

Field::Field(unsigned width, unsigned height, bool val) {
	this->width = width;
	this->height = height;
	this->my_field = field2d(width * height, val);
}

Field::Field(const field2d& f, unsigned width, unsigned height) {
	this->width = width;
	this->height = height;
	this->my_field = f;
}

Field::Field(const Field& f) noexcept {
	this->width = f.get_width();
	this->height = f.get_height();
	this->my_field = f.get_field();
}

void Field::set_field(const field2d& f) {
	if (f.size() != this->my_field.size()) throw std::runtime_error("Wrong size!\n");
	this->my_field = f;
}

unsigned Field::get_width() const noexcept {
	return this->width;
}

unsigned Field::get_height() const noexcept {
	return this->height;
}

field2d& Field::get_field() {
	return this->my_field;
}

field2d Field::get_field() const noexcept {
	return this->my_field;
}

void Field::set_cell(index2d idx, bool val) {
	this->my_field[idx.first * this->width + idx.second] = val;
}

bool Field::operator[](index2d idx) const {
	return this->my_field[idx.first * this->width + idx.second];
}

std::ostream& operator<<(std::ostream& out, const Field& f) {
	for (int i = 0; i <= f.get_height() + 1; i++) {
		bool c = (i == 0 || i == f.get_height() + 1);

		if (c) out << P;
		else out << V;

		for (int j = 0; j < f.get_width(); j++) {
			if (c) out << H;
			else out << (f[index2d(i - 1, j)] ? CELL : N_CELL);
		}

		if (c) out << P;
		else out << V;
		out << '\n';
	}
	return out;
}

/////////////////////////////////////////
//                                     //
//    LIFE FORMAT CLASS REALISATION    //
//                                     //
/////////////////////////////////////////

LifeFormat::LifeFormat() const {
	this->born_c = 0;
	this->surv_c = 0;
	this->name = str{"Untitled"};
}

LifeFormat::~LifeFormat() {}

LifeFormat::LifeFormat(int born, std::vector<int> survive) {

	this->born_c = born;
	this->surv_c = survive;
	this->name = str{"Untitled"};
}

LifeFormat::LifeFormat(int born, int survive, cells_vec cells) {

}

LifeFormat::LifeFormat(int born, int survive, str name) {

}

LifeFormat::LifeFormat(int born, int survive, cells_vec cells, str name) {

}

void LifeFormat::set_born(int born);
void LifeFormat::set_survive(int surv);
void LifeFormat::set_name(str name);
void LifeFormat::set_cells(cells_vec cells);

int LifeFormat::get_born() const noexcept;
int LifeFormat::get_survive() const noexcept;
str LifeFormat::get_name() const noexcept;
cells_vec LifeFormat::get_cells() const noexcept;

field2d LifeFormat::cells_to_field();
cells_vec LifeFormat::field_to_cells();
