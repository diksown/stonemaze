#include "simulation.h"

#include "board.h"
#include "lidi.h"

void Simulation::run(int lives, bool log, int sleepTimeMs, int iterations) {
    // Check if simulation was already run.
    if (lidiBoards.size() != 0) {
        std::cout << "Simulation was already run. Returning." << std::endl;
        return;
    }

    Board curBoard = initialBoard;
    LidiBoard curLidiBoard =
        LidiBoard::getLidiBoardWithOneParticle(curBoard.n, curBoard.m, lives);

    lidiBoards.push_back(curLidiBoard);
    if (log) display(curBoard, curLidiBoard);

    int curIteration = 0;
    while (iterations == -1 || curIteration < iterations) {
        if (sleepTimeMs != 0) {
            nap(sleepTimeMs);
        }
        curBoard.next();
        curLidiBoard = curLidiBoard.getNextLidiBoard(curBoard);
        lidiBoards.push_back(curLidiBoard);
        if (log) display(curBoard, curLidiBoard);
        curIteration++;
    }
}

void Simulation::display(Board bd, LidiBoard lidiBd) {
    std::vector<std::string> boardRepr = bd.repr(), lidiRepr = lidiBd.repr();
    assert(boardRepr.size() == lidiRepr.size());
    for (int i = 0; i < (int)boardRepr.size(); i++) {
        std::cout << boardRepr[i] << " | " << lidiRepr[i] << '\n';
    }

    std::cout << std::string(5 * bd.m + 2, '-') << '\n';
    std::cout << std::endl;
}