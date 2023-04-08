#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

void solve() {
    for (int i = 5; i <= 5; i++) {
        Board bd =
            Board::getBoardFromFile("input" + std::to_string(i) + ".txt");
        Simulation sim = Simulation(bd);

        int nLives = 1;
        sim.run(nLives, true, 0.1);
        std::cout << sim.result << std::endl;
    }
}

int main() { solve(); }
