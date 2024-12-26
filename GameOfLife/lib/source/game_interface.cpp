#include "../include/game_interface.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

void pop_n(str* string) {
    if (!string->empty() && (string->back() == '\n' || string->back() == '\r')) {
        string->pop_back();
    }
}

str get_line(int n, str line) {
    return "\t| at line " + std::to_string(n) + ": \033[0m" + line;
}


Universe* read_universe(const str name) {
    std::ifstream input(name);
    if (!input.is_open()) {
        throw std::invalid_argument("\033[0;91mError while opening file. Invalid file name or file missing.");
    }
    str line;
    if (!std::getline(input, line)) {
        throw std::invalid_argument("\033[0;91mYour file is empty.");
    }
    pop_n(&line);

    const str life = "#Life 1.06";
    if (line != life) {
        throw std::invalid_argument("\033[0;91mWrong file format. Call help command to learn more about the format.");
    }

    Universe* uni = new Universe();

    bool is_name = false;
    bool is_rule = false;
    bool is_size = false;
    int idx = 1;
    std::regex cell_pattern(R"(^([-+]?\d+)\s+([-+]?\d+$))");
    std::regex name_pattern(R"(^#N\s+(.+)$)");
    std::regex rule_pattern(R"(^#R\s+B(\d+)/S(\d+)$)");
    std::regex size_pattern(R"(^#S\s+(\d+)\s+(\d+)$)");
    std::smatch matches;
    while (std::getline(input, line)) {
        idx++;
        if (line.empty()) continue;
        pop_n(&line);
        if (std::regex_match(line, matches, name_pattern)) {
            if (is_name) {
                std::cout << "\033[1;93m" << "WARNING: ";
                std::cout << "\033[0;93m" << "More than one name is specified, the first occurrence will be used.\n" << get_line(idx, line) << "\n";
            }
            else {
                uni->set_name(matches[1]);
                is_name = true;
            }
        }
        else if (std::regex_match(line, matches, rule_pattern)) {
            if(is_rule) {
                std::cout << "\033[1;93m" << "WARNING: ";
                std::cout << "\033[0;93m" << "More than one rule is specified, the first occurrence will be used.\n" << get_line(idx, line) << "\n";
            }
            else {
                int_set tmp;
                str match = matches[1];
                for (int i = 0; i < matches[1].length(); i++) {
                    tmp.insert((int)(match[i] - '0'));
                }
                uni->set_birth(tmp);
                match = matches[2];
                for (int i = 0; i < matches[2].length(); i++) {
                    tmp.insert((int)(match[i] - '0'));
                }
                uni->set_survival(tmp);
                is_rule = true;
            }
        }
        else if (std::regex_match(line, matches, size_pattern)) {
            if (is_size) {
                throw std::invalid_argument("\033[0;91mSeveral sizes are indicated, please leave one size.");
            }
            else {
                Field tmp(std::stoi(matches[1]), std::stoi(matches[2]));
                uni->set_field(tmp);
                is_size = true;
            }
        }
        else if (std::regex_match(line, matches, cell_pattern)) {
            if (!is_size) {
                throw std::invalid_argument("\033[0;91mThe size is not specified, it is not possible to read the coordinates of the cells.");
            }
            int row = std::stoi(matches[1]);
            int col = std::stoi(matches[2]);
            if ((row < 0 || row >= uni->get_field().get_height()) || (col < 0 || col >= uni->get_field().get_height())) {
                std::cout << "\033[1;93m" << "WARNING: ";
                std::cout << "\033[0;93m" << "This coordinates of cell may be optimized.\n" << get_line(idx, line) << "\n";
            }
            try {
                uni->set_cell_err(row, col);
            }
            catch (std::invalid_argument err) {
                std::cout << "\033[1;93m" << "WARNING: ";
                std::cout << "\033[0;93m" << err.what() << "\n" << get_line(idx, line) << "\n";
            }
        }
        else {
            throw std::invalid_argument("\033[0;91mWrong format of file.\n" + get_line(idx, line));
        }

    }

    input.close();
    return uni;
}
void write_universe(const Universe& u, str name) {
    std::ofstream output(name);

    if (!output.is_open()) {
        throw std::invalid_argument("Error creating file. The path is incorrect or the file is already in use.");
    }

    try {
        Field tmp(u.get_field());
    }
    catch (std::runtime_error err) {
        throw std::invalid_argument("This universe have not Field object.");
    }

    Field tmp(u.get_field());
    output << "#Life 1.06\n\n";
    output << "#N " << u.get_name() << "\n";
    output << "#R B";
    int_set t = u.get_birth(); 
    for (auto it = t.begin(); it != t.end(); it++) {
        output << *it;
    }
    output << "/S";
    t = u.get_survival();
    for (auto it = t.begin(); it != t.end(); it++) {
        output << *it;
    }
    output << "\n";
    output << "#S " << tmp.get_width() << " " << tmp.get_height() << "\n\n";

    std::vector<std::pair<int, int>> points = tmp.get_points();
    for (int i = 0; i < points.size(); i++) {
        output << points[i].first << " " << points[i].second << "\n";
    }
    output << "\n";

    output.close();
}


