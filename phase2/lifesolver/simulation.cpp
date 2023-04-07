#include "simulation.h"

#include "board.h"
#include "lidi.h"

void Simulation::runAndShow(int lives, int sleepTime, int iterations) {
    Board curBoard = initialBoard;
    LidiBoard curLidiBoard = LidiBoard(initialBoard, lives);

    lidiBoards.push_back(curLidiBoard);
    display(curBoard, curLidiBoard);

    int curIteration = 0;
    while (iterations == -1 || curIteration < iterations) {
        display(curBoard, curLidiBoard);
        if (sleepTime != 0) {
            nap(sleepTime);
        }
        curBoard.next();
        curLidiBoard = curLidiBoard.getNextLidiBoard(curBoard);
        lidiBoards.push_back(curLidiBoard);
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