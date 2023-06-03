#include <cmath>
#include <random>
#include <array>
#include <iostream>
#include <vector>


unsigned long long table_width(const std::vector<std::vector<int>>& table) {
    return table.size();
}


unsigned long long table_height(const std::vector<std::vector<int>>& table) {
    return table[0].size();
}


///Returns the number of cells.
unsigned long long get_table_size(const std::vector<std::vector<int>>& table) {
    return table.size() * table[0].size();
}


///Calculates rate. Divides the sum of 1's by the table's size.
float get_rate(std::vector<std::vector<int>>& table) {
    float sum = 0;
    for(int i=0; i<table_width(table); i++){
        for(int j=0; j<table_height(table); j++) {
            if (table[i][j] == 1) {
                sum += 1;
            }
        }
    }
    return sum / get_table_size(table);
}


void print_table(const std::vector<std::vector<int>>& table) {
    for (const auto & i : table) {
        std::cout<<std::endl;
        for (int j : i) {
            std::cout << j << " ";
        }
    }
}


///Draws random index from range of all possible cells
int get_random_index(std::vector<std::vector<int>>& table) {
    return rand() % get_table_size(table) - 1;
}


///Converts index to coordinates
std::array<int,2> index_to_coords(int index, std::vector<std::vector<int>>& table) {
    int width = table_width(table);
    int x = floor(index / width);
    int y = index % width;
    std::array<int,2> coords = {x, y};
    return coords;
}


///Generates and returns random coordinates
std::array<int,2> get_random_coords(std::vector<std::vector<int>>& table, bool horizontal=false) {
    int index = get_random_index(table);
    std::array<int,2> coords = index_to_coords(index, table);
    //While clause handles horizontal end of scope pair matching error
    while (!horizontal && coords[1] == table_width(table) - 1) {
        index = get_random_index(table);
        coords = index_to_coords(index, table);
    }
    return coords;
}


///Look around for neighbour cells and return their coordinates
auto get_pair_neighbour_coords(std::vector<std::vector<int>>& table, std::array<int,2> start_coords) {
    int x = start_coords[0];
    int y = start_coords[1];

    std::array<int, 12> neighbour_coords = {x, y - 1, x, y + 2, x + 1, y, x + 1, y + 1, x - 1, y, x - 1, y + 1};
    return neighbour_coords;
}


float calculate_mean(const std::vector<float>& vec) {
    float sum = 0;
    for(float i : vec) {
        sum += i;
    }
    return sum / vec.size();
}


float calculate_std_dev(const std::vector<float>& vec, float ddof) {
    float mean = calculate_mean(vec);
    float std_dev = 0.0;
    for (float i : vec) {
        std_dev += pow(i - mean, 2);
    }
    unsigned long long var = (vec.size()*vec.size()) - ddof;
    return std::sqrt(std_dev / var);
}


///Adjusts spatial distribution of 1's and (-1)'s in order to receive desired ratio
void adjust_rate(std::vector<std::vector<int>>& table, float rate) {
    float actual_rate = get_rate(table);
    while (actual_rate != rate) {
        std::array<int,2> coords = get_random_coords(table, true);
        int x = coords[0];
        int y = coords[1];
        if (actual_rate < rate) {
            table[x][y] = 1;
        }
        else {
            table[x][y] = -1;
        }
        actual_rate = get_rate(table);
    }
}


///Returns a filled square table with a selected rate of spatial distribution of 1's and (-1)'s
std::vector<std::vector<int>> create_table(unsigned width, unsigned height, float rate) {
    //  if (sizeof(width * height * rate) != 4) {
    //       std::cout << "wrong rate.";
    //   }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({rate, 1-rate});
    int draw;

    std::vector<std::vector<int>> table(width, std::vector<int>(height));

    for (int i = 0; i<width; i++) {
        for (int j=0; j<height; j++) {
            draw = d(gen);
            if (draw == 0) {
                table[i][j] = 1;
            }
            else if (draw == 1) {
                table[i][j] = -1;
            }
        }
    }

    adjust_rate(table, rate);
    return table;
}


std::vector<std::vector<int>> create_square_table(unsigned width, float rate) {
    return create_table(width, width, rate);
}