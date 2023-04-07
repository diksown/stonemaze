#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    Board board = Board::randomBoard();

    Simulation sim(board);
    sim.runAndShow(1, true, 100);
}