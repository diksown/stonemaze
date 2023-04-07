#ifndef LIFESOLVER_SIMULATION_H
#define LIFESOLVER_SIMULATION_H

#include <cassert>
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

    void display(Board bd, LidiBoard lidiBd);

    // Runs the simulation for a given amount of iterations.
    // iterations = -1 => run until a particle reaches the bottom.
    // sleepTime = 0 => no sleep between iterations.

    void run(int lives = 1, bool log = false, int sleepTimeMs = 100,
             int iterations = -1);
};

#endif  // LIFESOLVER_SIMULATION_H