#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    Board board = Board::randomBoard(10, 10);
    std::cout << board << std::endl;
    Simulation sim = Simulation(board);
    sim.run(1, true, 1000);
}