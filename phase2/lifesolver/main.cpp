#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

void solve() {
    for (int i = 1; i <= 4; i++) {
        Board bd =
            Board::getBoardFromFile("input" + std::to_string(i) + ".txt");
        Simulation sim = Simulation(bd);

        int nLives = 1;
        if (i == 2) nLives = 6;
        sim.run(nLives, true);
        std::cout << sim.result << std::endl;
    }
}

int main() {
    // solve all challenges
    solve();
}
