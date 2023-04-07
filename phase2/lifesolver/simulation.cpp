#include "simulation.h"

#include "board.h"
#include "lidi.h"

void Simulation::runAndShow(int lives, bool log, int sleepTime,
                            int iterations) {
    Board curBoard = initialBoard;
    LidiBoard curLidiBoard = LidiBoard(initialBoard, lives);

    lidiBoards.push_back(curLidiBoard);
    if (log) display(curBoard, curLidiBoard);

    int curIteration = 0;
    while (iterations == -1 || curIteration < iterations) {
        if (log) {
            display(curBoard, curLidiBoard);
            ;
        }
        if (sleepTime != 0) {
            nap(sleepTime);
        }
        curBoard.next();
        curLidiBoard = curLidiBoard.getNextLidiBoard(curBoard);
        lidiBoards.push_back(curLidiBoard);
        curIteration++;
    }
}