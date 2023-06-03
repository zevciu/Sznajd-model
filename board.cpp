
#include "board.hpp"


Board::Board(int size, float distribution) {
    width = size;
    rate = distribution;
    table = create_square_table(width, rate);
}


int Board::is_pair_consistent(std::array<int,2> coord) {
    int x1 = coord[0];
    int y1 = coord[1];
    int x2 = coord[0];
    int y2 = coord[1] + 1;

    int value1 = table[x1][y1];
    int value2 = table[x2][y2];

    if (value1 == 1 and value2 == 1) {
        return 1;
    }
    if (value1 == -1 and value2 == -1) {
        return -1;
    }

    return 0;
}


std::array<int,2> Board::get_random_consistent_pair() {
    std::array<int,2> pair{};
    while (true) {
        pair = get_random_coords(table);
        if (is_pair_consistent(pair) != 0) {
            return pair;
        }
    }
}


void Board::fill_pair_neighbours(std::array<int,2> pair_start_coord) {
    int value = is_pair_consistent(pair_start_coord);
    std::array<int, 12> neighbour_coords = get_pair_neighbour_coords(table, pair_start_coord);

    for (int i=0; i<=sizeof(neighbour_coords)/sizeof(neighbour_coords[0]); i++) {
        if (neighbour_coords[i] < 0 || neighbour_coords[i+1] < 0 || neighbour_coords[i] >= table_width(table) || neighbour_coords[i+1] >= table_width(table))  {
            continue;
        }
        table[neighbour_coords[i]][neighbour_coords[i + 1]] = value;
    }

    rate = get_rate(table);
}


void Board::process(bool printable) {
    std::array<int,2> pair = get_random_consistent_pair();
    if (printable) {
        std::cout<<std::endl;
        int value = is_pair_consistent(pair);
        std::cout<<"Pair "<<"(["<<pair[0]<<","<<pair[1]<<"]["<<pair[0]<<","<<pair[1]+1<<"])"<<" is convincing its neighbours on "<<value;
    }
    fill_pair_neighbours(pair);
    if (printable) {
        std::cout<<std::endl<<"Updating the table"<<std::endl;
        print_table(table);
        std::cout<<std::endl<<"Agreement rate = "<<rate;
    }
}


std::vector<float> Board::simulate(int iterations,
                            bool printable,
                            bool track,
                            bool until_stability) {

    std::vector<float> agreement_array;

    if (until_stability) {
        int iterations_count = 0;
        while (true) {
            process(printable);
            if (track) {
                agreement_array.push_back(rate);
            }
            iterations_count += 1;
            if (rate == 1 || rate == 0) {
                std::cout<<"The simulation has reached stability after: "<<iterations_count<<std::endl;
                std::cout<<"All actors reached a state of: "<<rate<<std::endl;
                if (track) {
                    return agreement_array;
                }
                else {
                    break;
                }
            }

        }
    }
    else {
        for (int i=0; i<=iterations; i++) {

            process(printable);
            if (track) {
                agreement_array.push_back(rate);
            }
        }
        if (track) {
            return agreement_array;
        }
        else {
            std::vector<float> last_agreement;
            last_agreement.push_back(rate);
            return last_agreement;
        }
    }
}


void Board::print_p0() const {
    print_table(table);
    std::cout<<std::endl<<"Agreement rate = "<<rate;
}
