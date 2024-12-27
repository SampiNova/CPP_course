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
    /**
     * @brief Default constructor for Field class.
     *
     * Initializes a 3x3 field with all cells set to false.
     * @param None
     * @return None
     */
    Field();
    /**
     * @brief Destructor for Field class.
     *
     *  @param None
     * @return None
     */
    ~Field();
     /**
     * @brief Copy constructor for Field class.
     *
     * @param f The Field object to copy from.
     * @return None
     */
    Field(const Field& f);
     /**
     * @brief Parameterized constructor for Field class.
     *
     * @param width The width of the field.
     * @param height The height of the field.
     * @param value The initial value of all cells (default is false).
     * @throws std::invalid_argument if width or height is less than 3.
     * @return None
     */
    Field(int width, int height, bool value=false);
    /**
     * @brief Returns the width of the field.
     *
     * @param None
     * @return The width of the field.
     */
    int get_width() const;
    /**
     * @brief Returns the height of the field.
     *
     * @param None
     * @return The height of the field.
     */
    int get_height() const;
    /**
     * @brief Returns the underlying field data.
     *
     * @param None
     * @return A vector of booleans representing the field.
     */
    field_type get_field() const;
    /**
     * @brief Returns the value of a cell at given coordinates.
     *
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @return True if the cell is alive, false otherwise.
     * Coordinates are wrapped around if they are out of bounds.
     */
    bool at(int row, int col) const;
     /**
     * @brief Calculates the number of live neighbors for a given cell.
     *
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @return The number of live neighbors.
     * Wraps around coordinates if they are out of bounds.
     */
    int get_neighbours(int row, int col) const;
    /**
     * @brief Returns a vector of coordinates of all live cells in the field.
     *
     * @param None
     * @return A vector of pairs of integers, where each pair represents a row and column of a live cell.
     */
    std::vector<std::pair<int, int>> get_points() const;
    /**
     * @brief Sets the value of a cell at given coordinates.
     *
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @param value The value to set (default is true).
     * Coordinates are wrapped around if they are out of bounds.
     * @return None
     */
    void set_at(int row, int col, bool value=true);
    /**
     * @brief Sets the field to the given values.
     *
     * @param f The new field data.
     * @throws std::invalid_argument if the input vector size is too small or doesn't match the field size.
     * @return None
     */
    void set_field(const field_type& f);
};
/**
 * @brief Compares two Field objects for equality.
 *
 * @param f1 The first Field object.
 * @param f2 The second Field object.
 * @return True if both fields have the same dimensions and cell values, false otherwise.
 */
bool operator==(const Field& f1, const Field& f2);
/**
 * @brief Overloads the output stream operator for printing a field.
 *
 * @param out The output stream.
 * @param f The field to be printed.
 * @return The output stream for chaining.
 */
std::ostream& operator<<(std::ostream& out, const Field& f);


class Universe {
private:
    str name;
    int_set birth;
    int_set survival;
    Field* field;
    int ticks_cnt;
public:
    /**
     * @brief Default constructor for Universe class.
     * Initializes the universe with default name, birth and survival rules and 3x3 field.
     * @param None
     * @return None
     */
    Universe();
    /**
     * @brief Destructor for Universe class.
     * Deallocates memory for field.
     *  @param None
     * @return None
     */
    ~Universe();
     /**
     * @brief Copy constructor for Universe class.
     *
     * @param u The Universe object to copy from.
     * @return None
     */
    Universe(const Universe& u);
     /**
     * @brief Parameterized constructor for Universe class.
     *
     * @param width The width of the field.
     * @param height The height of the field.
     * @param value The initial value of all cells (default is false).
     * @throws std::invalid_argument if width or height is less than 3.
     * @return None
     */
    Universe(int width, int height, bool value=false);
    /**
     * @brief Parameterized constructor for Universe class.
     *
     * @param name The name of the universe.
     * @param birth The set of neighbor counts for a cell to be born.
     * @param survival The set of neighbor counts for a cell to survive.
     * @param width The width of the field.
     * @param height The height of the field.
     * @param value The initial value of all cells (default is false).
     * @throws std::invalid_argument if width or height is less than 3.
     * @return None
     */
    Universe(str name, int_set birth, int_set survival, int width, int height, bool value=false);
    /**
     * @brief Parameterized constructor for Universe class.
     *
     * @param name The name of the universe.
     * @param birth The set of neighbor counts for a cell to be born.
     * @param survival The set of neighbor counts for a cell to survive.
     * @param f The field to initialize the universe with.
     * @return None
     */
    Universe(str name, int_set birth, int_set survival, const Field& f);
    /**
     * @brief Returns the name of the universe.
     *
     * @param None
     * @return The name of the universe.
     */
    str get_name() const;
    /**
     * @brief Returns the set of neighbor counts for a cell to be born.
     *
     * @param None
     * @return The set of neighbor counts for a cell to be born.
     */
    int_set get_birth() const;
    /**
     * @brief Returns the set of neighbor counts for a cell to survive.
     *
     * @param None
     * @return The set of neighbor counts for a cell to survive.
     */
    int_set get_survival() const;
     /**
     * @brief Returns the reference to the field of the universe.
     *
     * @param None
     * @return Reference to field object.
     * @throws std::runtime_error if field is empty.
     */
    Field& get_field() const;
    /**
     * @brief Returns the number of ticks.
     *
     * @param None
     * @return The number of ticks.
     */
    int get_ticks() const;
    /**
     * @brief Sets the name of the universe.
     *
     * @param name The new name of the universe.
     * @return None
     */
    void set_name(str name);
    /**
     * @brief Sets the set of neighbor counts for a cell to be born.
     *
     * @param birth The new set of neighbor counts for a cell to be born.
     * @return None
     */
    void set_birth(int_set birth);
    /**
     * @brief Sets the set of neighbor counts for a cell to survive.
     *
     * @param survival The new set of neighbor counts for a cell to survive.
     * @return None
     */
    void set_survival(int_set survival);
    /**
     * @brief Sets the field of the universe.
     *
     * @param f The new field to set.
     * @return None
     */
    void set_field(const Field& f);
    /**
     * @brief Sets the value of a cell at given coordinates.
     *
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @param value The value to set (default is true).
     * @throws std::runtime_error if field is empty.
     * @return None
     */
    void set_cell(int row, int col, bool value=true);
    /**
     * @brief Sets the value of a cell at given coordinates and throws error if this cell have already setted this value.
     *
     * @param row The row of the cell.
     * @param col The column of the cell.
     * @param value The value to set (default is true).
     * @throws std::runtime_error if field is empty.
     * @throws std::invalid_argument if cell already have this value.
     * @return None
     */
    void set_cell_err(int row, int col, bool value=true);
    /**
     * @brief Sets the number of ticks.
     *
     * @param ticks The new number of ticks.
     * @throws std::invalid_argument if ticks is less than 0.
     * @return None
     */
    void set_ticks(int ticks=0);
    /**
     * @brief Performs one tick of the simulation, updating the field.
     *
     * @param None
     * @return True if the field has changed, false otherwise.
     * @throws std::runtime_error if field is empty.
     */
    bool tick();
};
