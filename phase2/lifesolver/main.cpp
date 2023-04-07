#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    Board bd = Board::getBoardFromFile("input11.txt");
    Simulation sim = Simulation(bd);
    sim.run(1, true);
    std::cout << sim.result << std::endl;
}
