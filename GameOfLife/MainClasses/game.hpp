#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define CELL "@"
#define N_CELL "."

using row_type = std::vector<bool>;
using field_type = std::vector<row_type>;

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

    bool empty() const;
    int get_width() const;
    int get_height() const;
    field_type get_field() const;
    bool at(int row, int col) const;

    void set_at(int row, int col, bool value=true);
    void set_field(const field_type& f);
};

std::ostream& operator<<(std::ostream& out, const Field& f);


class Universe {
private:
    Field field;
public:
    Universe();
    ~Universe();
};

