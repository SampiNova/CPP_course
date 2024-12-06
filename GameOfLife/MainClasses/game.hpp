#pragma once
#include <iostream>
#include <algorithm>

#define CELL '@'
#define N_CELL ' '
#define V '|'
#define H '-'
#define P '+'

using index2d = std::pair<unsigned, unsigned>;
using field2d = std::vector<bool>;
using str = std::string;
using cells_vec = std::map<std::pair<int, int>>;

class Field {
protected:
	field2d my_field;
	int width;
	int height;
public:
	Field() noexcept;
	~Field();
	Field(unsigned width, unsigned height, bool val=0);
	Field(const field2d& f, unsigned width, unsigned height);
	Field(const Field& f) noexcept;

	void set_field(const field2d& f);

	unsigned get_width() const noexcept;
	unsigned get_height() const noexcept;
	field2d& get_field();
	field2d get_field() const noexcept;

	void set_cell(index2d idx, bool val=1);
	bool operator[](index2d idx) const;
};

std::ostream& operator<<(std::ostream& out, const Field& f);


class LifeFormat {
private:
	int born_c;
	int surv_c;
	str name;
	cells_vec cells;
public:
	LifeFormat() const;
	~LifeFormat();
	LifeFormat(int born, int survive);
	LifeFormat(int born, int survive, cells_vec cells);
	LifeFormat(int born, int survive, str name);
	LifeFormat(int born, int survive, cells_vec cells, str name);

	void set_born(int born);
	void set_survive(int surv);
	void set_name(str name);
	void set_cells(cells_vec cells);

	int get_born() const noexcept;
	int get_survive() const noexcept;
	str get_name() const noexcept;
	cells_vec get_cells() const noexcept;

	field2d cells_to_field();
	cells_vec field_to_cells();
};
