#ifndef LIFESOLVER_SIMULATION_H
#define LIFESOLVER_SIMULATION_H

#include <cassert>
#include <iostream>
#include <vector>

#include "board.h"
#include "lidi.h"
#include "utils.h"

// Will hold the result of a simulation, when a path is found.
struct SimulationResult {
    std::vector<char> path;
    int nIterations;
    std::string pathString();
};

// Will take a board as input and run a simulation on it.
struct Simulation {
    Board initialBoard;
    std::vector<LidiBoard> lidiBoards;
    SimulationResult result;

    Simulation(Board board) : initialBoard(board) {}

    static void display(Board bd, LidiBoard lidiBd);

    // Runs the simulation for a given amount of iterations.
    // iterations = -1 => run until a particle reaches the bottom.
    // sleepTime = 0 => no sleep between iterations.
    SimulationResult run(int lives = 1, bool log = false,
                         double sleepTimeSeconds = 0, int iterations = -1);

    SimulationResult getResult();
};

std::ostream& operator<<(std::ostream& o, SimulationResult& result);

#endif  // LIFESOLVER_SIMULATION_H