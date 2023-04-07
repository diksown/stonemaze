#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    Board board = Board::randomBoard(5, 10, 3);
    Simulation sim = Simulation(board);
    sim.run(1, true, 0, 10);
}