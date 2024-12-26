#pragma once
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define CELL "\033[1;92m\u25A0\033[0;0m "
#define N_CELL "\033[0;90m\u25FB\033[0;0m "

using field_type = std::vector<bool>;
using str = std::string;
using int_set = std::set<int>;

class Field {
private:
    field_type field;
    int width;
    int height;
public:
    Field();
    ~Field();
    Field(const Field& f);
    Field(int width, int height, bool value=false);

    int get_width() const;
    int get_height() const;
    field_type get_field() const;
    bool at(int row, int col) const;
    int get_neighbours(int row, int col) const;
    std::vector<std::pair<int, int>> get_points() const;

    void set_at(int row, int col, bool value=true);
    void set_field(const field_type& f);
};

bool operator==(const Field& f1, const Field& f2);

std::ostream& operator<<(std::ostream& out, const Field& f);


class Universe {
private:
    str name;
    int_set birth;
    int_set survival;
    Field* field;
    int ticks_cnt;
public:
    Universe();
    ~Universe();
    Universe(const Universe& u);
    Universe(int width, int height, bool value=false);
    Universe(str name, int_set birth, int_set survival, int width, int height, bool value=false);
    Universe(str name, int_set birth, int_set survival, const Field& f);

    str get_name() const;
    int_set get_birth() const;
    int_set get_survival() const;
    Field& get_field() const;
    int get_ticks() const;

    void set_name(str name);
    void set_birth(int_set birth);
    void set_survival(int_set survival);
    void set_field(const Field& f);
    void set_cell(int row, int col, bool value=true);
    void set_cell_err(int row, int col, bool value=true);
    void set_ticks(int ticks=0);

    bool tick();
};

