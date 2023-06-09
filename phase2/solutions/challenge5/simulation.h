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
    int pathLen;
    std::string pathString();
    SimulationResult() : pathLen(-1) {}
};

// Will take a board as input and run a simulation on it.
struct Simulation {
    Board initialBoard;
    std::vector<LidiBoard> lidiBoards;
    SimulationResult result;
    int minDistance = 1e9;
    int lBest = -1;
    int rBest = -1;

    Simulation(Board board) : initialBoard(board) {}

    static void display(Board bd, LidiBoard lidiBd);

    // Runs the simulation for a given amount of iterations.
    // iterations = -1 => run until a particle reaches the bottom.
    // sleepTime = 0 => no sleep between iterations.
    SimulationResult run(int lives = 1, bool log = false,
                         double sleepTimeSeconds = 0, int iterations = -1);

    SimulationResult backtrackFrom(int line, int col, int ind);
    SimulationResult getResult();
    SimulationResult getResultClosest();
};

std::ostream& operator<<(std::ostream& o, SimulationResult& result);

std::ostream& operator<<(std::ostream& o, Simulation& sim);

#endif  // LIFESOLVER_SIMULATION_H