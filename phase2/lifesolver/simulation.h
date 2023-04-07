#ifndef LIFESOLVER_SIMULATION_H
#define LIFESOLVER_SIMULATION_H

#include <iostream>
#include <vector>

#include "board.h"
#include "lidi.h"
#include "utils.h"

// Will take a board as input and run a simulation on it.
struct Simulation {
    Board initialBoard;
    std::vector<LidiBoard> lidiBoards;

    Simulation(Board board) : initialBoard(board) {}

    // Runs the simulation for a given amount of iterations.
    // If iterations is -1, it will run until a particle reaches the edge of the
    // board. If sleepTime is not 0, it will sleep for that amount of
    // milliseconds between each iteration. If log is true, it will print the
    // board + lidiBoard after each iteration.
    void runAndShow(int iterations = -1, int lives = 1, int sleepTime = 0,
                    bool log = false) {
        Board curBoard = initialBoard;  // Is this really the best approach for
                                        // the parameters?
        LidiBoard curLidiBoard = LidiBoard(initialBoard, lives);
    }
};

#endif  // LIFESOLVER_SIMULATION_H