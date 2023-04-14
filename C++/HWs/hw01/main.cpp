#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <valarray>
#include "parse.hpp"

// macros
#define OUT_OF_RANGE 100
#define INVALID_INPUT 101
#define INVALID_CONFIGURATION 102
#define CELL_TOO_SHORT 103

int error(int type_of_error);

void print_border(const cfg_values_t &all_cfg_values, int table_width, int header);

void print_config(cfg_values_t &all_cfg_values);

long max_number_digits(const cfg_values_t &all_cfg_values);

int GetNumberOfDigits(int i);

void print_table_right(int maxRow, unsigned long numberOfMax, const std::vector<std::vector<int>> &values, int count,
                       cfg_values_t &all_cfg_values, int &header);

void print_table_left(int maxRow, unsigned long numberOfMax, const std::vector<std::vector<int>> &values, int count,
                      cfg_values_t &all_cfg_values, int &header);

int main() {
    // variable for decoded config
    config_t config;
    std::string line;
    cfg_values_t all_cfg_values = get_default_cfg_values();
    int maxRow = -1;
    do {
        std::getline(std::cin, line);
        config = getConfig(line);
        if (config.valid) {
            all_cfg_values = set_cfg_values(all_cfg_values, config);
        }
    } while (config.valid);

    long numberOfMax = max_number_digits(all_cfg_values);

    std::vector<std::vector<int>> values;

    int count = 0;
    while (std::getline(std::cin, line)) {
        count++;
        std::stringstream ss(line);
        std::vector<int> row;
        std::string cell;
        int number;
        int add_sum = 0;

        while (std::getline(ss, cell, ';')) {
            try {   // if loaded cell is number
                number = std::stoi(cell);
                if ((number < all_cfg_values.min) || (number > all_cfg_values.max)) { // if number is out of range
                    error(1);
                }
                row.push_back(number);
            }
            catch (const std::exception &e) { // if there is a text (SUM?)
                if ((cell.find("SUM") != 0) ||
                    (getSum(line, row).valid == 0)) { // something different then number or word SUM and SUM is invalid
                    error(2);
                }
                int sum = getSum(line, row).value;
                row.push_back(sum + add_sum);
                add_sum = sum; // add_sum is for multiple SUM in one line
            }

        }
        if (static_cast<int>(row.size()) > maxRow) {
            maxRow = static_cast<int>(row.size());
        }
        values.push_back(row);
    }

    if ((all_cfg_values.min > all_cfg_values.max) ||
        (all_cfg_values.width < 1)) { // min > max or width is negative number
        error(3);
    }
    if ((all_cfg_values.width < numberOfMax) && (all_cfg_values.stretch == -1)) { // cell is too small for the number
        error(4);
    }
    if (all_cfg_values.stretch == 1) {
        all_cfg_values.width = numberOfMax; // set config.width to stretched value
    }

    print_config(all_cfg_values);

    //printing table
    int header;
    if (all_cfg_values.align == "left") { // align left
        print_table_left(maxRow, numberOfMax, values, count, all_cfg_values, header);
    }
    if (all_cfg_values.align == "right") { //align right
        print_table_right(maxRow, numberOfMax, values, count, all_cfg_values, header);
    }
    print_border(all_cfg_values, maxRow, header);
    return 0;
}

void print_table_left(int maxRow, unsigned long numberOfMax, const std::vector<std::vector<int>> &values, int count,
                      cfg_values_t &all_cfg_values, int &header) {
    header = 0;
    unsigned int table_high = count; //high of table
    unsigned int table_width = maxRow + 1;
    std::string letter{
            "A" "B" "C" "D" "E" "F" "G" "H" "I" "J" "K" "L" "M" "N" "O" "P" "Q" "R" "S" "T" "U" "V" "W" "X" "Y" "Z"};
    if (all_cfg_values.header == 0) {
        header = 1;
        table_width--;
        table_high--;
    }
    if (all_cfg_values.stretch == 1) {
        all_cfg_values.width = numberOfMax;
    }

    for (unsigned int i = 0; i < table_high + 1; ++i) {
        print_border(all_cfg_values, maxRow, header);
        for (unsigned int j = 0; j < table_width; ++j) {
            // print values
            std::stringstream inside;
            if ((i == 0) && (j == 0) && (all_cfg_values.header == 1)) { // left up place
                inside << "| " << std::setw(all_cfg_values.width + 1) << " ";
                std::cout << inside.str();
            } else if ((i == 0) && (all_cfg_values.header == 1)) { //first row
                inside << "| " << std::setw(all_cfg_values.width) << std::left << letter[j - 1] << " ";
                std::cout << inside.str();
            } else if ((j == 0) && (all_cfg_values.header == 1)) { //first colum
                inside << "| " << std::setw(all_cfg_values.width) << std::left << i << " ";
                std::cout << inside.str();
            } else {
                if (j > values[i - 1 + header].size()) {
                    inside << "| " << std::setw(all_cfg_values.width + 1)
                           << " "; // if in row is not another values ---> blank space
                } else { //printing numbers
                    if (all_cfg_values.stretch == 1) {
                        inside << "| " << std::setw(all_cfg_values.width) << std::left
                               << values[i - 1 + header][j - 1 + header]
                               << " ";
                    } else if ((all_cfg_values.stretch == 0) &&
                               (GetNumberOfDigits(values[i - 1][j - 1]) > all_cfg_values.width)) {
                        inside << "| " << std::setw(all_cfg_values.width) << std::left
                               << std::string(all_cfg_values.width, '#')
                               << " ";
                    } else {
                        inside << "| " << std::setw(all_cfg_values.width) << std::left
                               << values[i - 1 + header][j - 1 + header]
                               << " ";
                    }
                }
                std::cout << inside.str();
            }
        }
        std::cout << "|" << std::endl;
    }
}

void print_table_right(int maxRow, unsigned long numberOfMax, const std::vector<std::vector<int>> &values, int count,
                       cfg_values_t &all_cfg_values, int &header) {
    header = 0;
    unsigned int table_high = count; //high of table
    unsigned int table_width = maxRow + 1;
    std::string letter{
            "A" "B" "C" "D" "E" "F" "G" "H" "I" "J" "K" "L" "M" "N" "O" "P" "Q" "R" "S" "T" "U" "V" "W" "X" "Y" "Z"};
    if (all_cfg_values.header == 0) {
        header = 1;
        table_width--;
        table_high--;
    }
    if (all_cfg_values.stretch == 1) {
        all_cfg_values.width = numberOfMax;
    }

    for (unsigned int i = 0; i < table_high + 1; ++i) {
        print_border(all_cfg_values, maxRow, header);
        for (unsigned int j = 0; j < table_width; ++j) {
            // print values
            std::stringstream inside;
            if ((i == 0) && (j == 0) && (all_cfg_values.header == 1)) { // left up place
                inside << "| " << std::setw(all_cfg_values.width + 1) << " ";
                std::cout << inside.str();
            } else if ((i == 0) && (all_cfg_values.header == 1)) { //first row
                inside << "| " << std::setw(all_cfg_values.width) << letter[j - 1] << " ";
                std::cout << inside.str();
            } else if ((j == 0) && (all_cfg_values.header == 1)) { //first colum
                inside << "| " << std::setw(all_cfg_values.width) << i << " ";
                std::cout << inside.str();
            } else {
                if (j > values[i - 1 + header].size()) {
                    inside << "| " << std::setw(all_cfg_values.width + 1)
                           << " "; // if in row is not another values ---> blank space
                } else { //printing numbers
                    if (all_cfg_values.stretch == 1) {
                        inside << "| " << std::setw(all_cfg_values.width) << values[i - 1 + header][j - 1 + header]
                               << " ";
                    } else if ((all_cfg_values.stretch == 0) &&
                               (GetNumberOfDigits(values[i - 1][j - 1]) > all_cfg_values.width)) {
                        inside << "| " << std::setw(all_cfg_values.width) << std::string(all_cfg_values.width, '#')
                               << " ";
                    } else {
                        inside << "| " << std::setw(all_cfg_values.width) << values[i - 1 + header][j - 1 + header]
                               << " ";
                    }
                }
                std::cout << inside.str();
            }
        }
        std::cout << "|" << std::endl;
    }
}

int GetNumberOfDigits(int i) {
    return i > 0 ? (int) log10((double) i) + 1 : 1;
}

long max_number_digits(const cfg_values_t &all_cfg_values) {
    int max_number = all_cfg_values.max;
    std::stringstream max_numb_in_str;
    max_numb_in_str << max_number;
    long numberOfMax = max_numb_in_str.str().length(); //max number od digits
    return numberOfMax;
}

void print_config(cfg_values_t &all_cfg_values) {
    printCfgValues(all_cfg_values); //printing config
    if (all_cfg_values.header != 1) {
        printCfgValue(HEADER_TYPE, std::to_string(all_cfg_values.header));
    }
    if (all_cfg_values.stretch != -1) {
        printCfgValue(STRETCH_TYPE, std::to_string(all_cfg_values.stretch));
    }
    std::cout << "\n";
}

void print_border(const cfg_values_t &all_cfg_values, int table_width, int header) {
    std::stringstream border;
    border << "+" << std::string(all_cfg_values.width + 2, '-');
    for (int x = 0; x < table_width + 1 - header; ++x) {
        std::cout << border.str();
    }
    std::cout << "+\n";
}

int error(int type_of_error) {
    switch (type_of_error) {
        case 1:
            std::cerr << "Out of range" << std::endl;
            exit(OUT_OF_RANGE);
        case 2:
            std::cerr << "Invalid input" << std::endl;
            exit(INVALID_INPUT);
        case 3:
            std::cerr << "Invalid configuration" << std::endl;
            exit(INVALID_CONFIGURATION);
        case 4:
            std::cerr << "Cell is too short" << std::endl;
            exit(CELL_TOO_SHORT);
        default:
            std::cerr << "Different error" << std::endl;
            exit(-1);
    }

}

