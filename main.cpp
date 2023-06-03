#include "table_utils.cpp"
#include "board.cpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;


/* Iterates simulations and returns a vector of final agreement rates of each simulation iteration.
         * First parameter is the size of the table
         * Second parameter is the initial rate of the table
         * Third parameter sets the time of simulation.
         * Std_dev flag set to true returns standard deviation of the above-mentioned vector.
         */
std::vector<float> iterate_simulations(int size,
                                  float rate,
                                  int in_iterations,
                                  int out_iterations,
                                  bool std_dev=false) {

    std::vector<float> last_states;
    std::vector<float> outcomes;

    for (int i=0; i<=out_iterations; i++) {
        auto* board = new Board(size, rate);
        std::vector<float> last_agreement = board->simulate(in_iterations);
        last_states.push_back(last_agreement[0]);
    }
    if (std_dev) {
        outcomes.push_back(calculate_mean(last_states));
        outcomes.push_back(calculate_std_dev(last_states, 1));
        return outcomes;
    }
    else {
        return last_states;
    }
}


void run_exercise(int n_of_exercise) {

    switch(n_of_exercise) {
        case 1: {
            std::cout<<std::endl<<"Exercise 1"<<std::endl;

            auto* board = new Board(10, 0.5);
            board->print_p0();
            board->simulate(20, true);
            break;
        }
        case 2: {
            std::cout<<std::endl<<"Exercise 2"<<std::endl;

            auto* board = new Board(14, 0.5);
            std::vector<float> track_evol = board->simulate(0, false, true, true);

            std::vector<int> x_axis;
            for (int i = 0; i<track_evol.size(); i++) {
                x_axis.push_back(i);
            }

            plt::xlabel("Time (t)");
            plt::ylabel("Agreement rate (p)");
            plt::title("Time evolution of the fraction ρ (t) of 'yes' actors");
            plt::plot(x_axis, track_evol);
            plt::show();

            break;
        }
        case 3: {
            std::cout<<std::endl<<"Exercise 3"<<std::endl;

            std::vector<float> mean;
            std::vector<float> std;
            std::vector<float> p0 = {0.25, 0.25, 0.25, 0.5, 0.5, 0.5, 0.75, 0.75, 0.75};
            std::vector<int> R = {10, 1000, 100000, 10, 1000, 100000, 10, 1000, 100000};
            std::vector<std::vector<float>> std_mean_pairs;

            std_mean_pairs.push_back(iterate_simulations(14, 0.25, 1091, 10, true));
            std_mean_pairs.push_back(iterate_simulations(14, 0.25, 1091, 1000, true));
            std_mean_pairs.push_back(iterate_simulations(14, 0.25, 1091, 100000, true));

            std_mean_pairs.push_back(iterate_simulations(14, 0.5, 2252, 10, true));
            std_mean_pairs.push_back(iterate_simulations(14, 0.5, 2252, 1000, true));
            std_mean_pairs.push_back(iterate_simulations(14, 0.5, 2252, 100000, true));

            std_mean_pairs.push_back(iterate_simulations(14, 0.75, 711, 10, true));
            std_mean_pairs.push_back(iterate_simulations(14, 0.75, 711, 1000, true));
            std_mean_pairs.push_back(iterate_simulations(14, 0.75, 711, 100000, true));

            for (auto & std_mean_pair : std_mean_pairs) {
                mean.push_back(std_mean_pair[0]);
                std.push_back(std_mean_pair[1]);
            }

            std::cout<<"p0"<<"       "<<"R"<<"      "<<"Mean"<<"         "<<"Std_Dev"<<std::endl;
            for (int i=0; i<mean.size(); i++) {

                std::cout<<p0[i]<<"     "<<R[i]<<"     "<<mean[i]<<"     "<<std[i]<<std::endl;
            }

            break;
        }

        default:
            std::cout<<"Pick a number of exercise (1-3)";
            break;
    }
}


int main() {

    run_exercise(1);
    return 0;
}