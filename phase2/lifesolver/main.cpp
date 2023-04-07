#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    int bigsize = 5;
    Board board = Board::randomBoard(bigsize, bigsize, 1);
    Simulation sim = Simulation(board);
    sim.run(1, true, 0.5);
    std::cout << sim.result << std::endl;
}