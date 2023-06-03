
#ifndef SZNAJD_MODEL_BOARD_H
#define SZNAJD_MODEL_BOARD_H


class Board {

private:
    int width;
    float rate;
    std::vector <std::vector<int>> table;

public:
    Board(int size, float distribution);

    ///Returns value of 1 or (-1) if pair is consistent in one way or other or 0 if pair doesn't match
    int is_pair_consistent(std::array<int,2> coord);

    ///Scans for and then returns a consistent pair (that equals to either 1 or (-1))
    std::array<int,2> get_random_consistent_pair();

    ///Simulation logic: A consistent pair (convinces) changes the state of their neighbors
    void fill_pair_neighbours(std::array<int,2> pair_start_coord);

    /* Fetches random consistent pair and changes the state of their neighbours
    * Additional info of the process with printable flag set to true
    */
    void process(bool printable=false);

    /* Starts the simulation of Sznajd model. Returns the value of last agreement rate.
     * If track flag set to True: Tracks agreement rate each iteration. Returns vector of these values.
     * If until_stability flag set to true -> loops simulation until stability.
     * Prints number of iterations after stability is reached.
     */
    std::vector<float> simulate(int iterations=0,
                                bool printable=false,
                                bool track=false,
                                bool until_stability=false);


    void print_p0() const;
};


#endif //SZNAJD_MODEL_BOARD_H
