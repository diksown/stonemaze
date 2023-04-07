#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    int bigsize = 500;
    Board board = Board::randomBoard(bigsize, bigsize);
    Simulation sim = Simulation(board);
    sim.run(6, false, 0, bigsize);
}