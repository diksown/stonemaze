#ifndef LIFESOLVER_SIMULATION_H
#define LIFESOLVER_SIMULATION_H

#include <iostream>
#include <vector>

#include "board.h"
#include "lidi.h"
#include "utils.h"

// Will take a board as input and run a simulation on it.
struct Simulation {
    Board board;
    LidiBoard lidiBoard;
    std::vector<LidiBoard> lidiBoards;

    Simulation(Board board) : board(board), lidiBoard(LidiBoard(board)) {}

    void run(int iterations = 10) {
        for (int i = 0; i < iterations; i++) {
            board.next();
            LidiBoard newLidiBoard = lidiBoard.getNextLidiBoard(board);
            lidiBoards.push_back(newLidiBoard);
            board.print();
            std::cout << std::endl;
            newLidiBoard.print();
            std::cout << std::endl;
            sleep();
        }
    }
};

#endif  // LIFESOLVER_SIMULATION_H