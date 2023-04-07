#include "simulation.h"

#include "board.h"
#include "lidi.h"
#include "utils.h"

void Simulation::run(int lives, bool log, double sleepTimeSeconds,
                     int iterations) {
    // Check if simulation was already run.
    if (lidiBoards.size() != 0) {
        warn("Simulation was already run.");
        return;
    }

    Board curBoard = initialBoard;
    LidiBoard curLidiBoard =
        LidiBoard::getLidiBoardWithOneParticle(curBoard.n, curBoard.m, lives);

    lidiBoards.push_back(curLidiBoard);
    if (log) display(curBoard, curLidiBoard);

    int curIteration = 0;
    while (iterations == -1 || curIteration < iterations) {
        if (sleepTimeSeconds != 0) {
            nap(sleepTimeSeconds);
        }
        curBoard.next();
        curLidiBoard = curLidiBoard.getNextLidiBoard(curBoard);
        lidiBoards.push_back(curLidiBoard);
        if (log) display(curBoard, curLidiBoard);
        curIteration++;
    }
}

std::string getLightLine(int boardWidth) {
    std::string lightLine = "";
    for (int i = 0; i < 2 * boardWidth + 4; i++) {
        lightLine += "░";
    }
    lightLine += "\n";
    return lightLine;
}

void Simulation::display(Board bd, LidiBoard lidiBd) {
    std::vector<std::string> boardRepr = bd.repr(), lidiRepr = lidiBd.repr();
    assert(boardRepr.size() == lidiRepr.size());

    std::string lightLine = getLightLine(bd.m);

    std::cout << lightLine;
    for (int i = 0; i < (int)boardRepr.size(); i++) {
        std::cout << boardRepr[i] << " | " << lidiRepr[i] << '\n';
    }

    std::cout << lightLine;
    std::cout << std::endl;
}