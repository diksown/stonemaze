#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

int main() {
    Board board = Board::randomBoard(5, 5);
    LidiBoard lidiBoard = LidiBoard::getLidiBoardWithOneParticle(board);
    for (int i = 0; i < 10; i++) {
        Simulation::display(board, lidiBoard);
        nap(2e3);
        board.next();
        lidiBoard = lidiBoard.getNextLidiBoard(board);
    }
}