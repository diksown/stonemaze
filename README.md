# Stonemaze

<pre>Soluções para o Stone Automata Maze Challenge<pre>

Esse repositório contém as minhas soluçoes para o desafio da Stone + SigmaGeek.

Eram 5 desafios com variações entre eles, mas do jeito que eu fiz, acabei usando o mesmo algoritmo para os challenges 1, 2, 3 e 4.


O algoritmo geral se encontra na pasta `phase2/lifesolver`:

```
cd phase2/lifesolver
cat main.cpp
#include <iostream>

#include "board.h"
#include "lidi.h"
#include "simulation.h"
#include "utils.h"

void solve() {
    for (int i = 1; i <= 5; i++) {
        Board bd =
            Board::getBoardFromFile("input" + std::to_string(i) + ".txt");
        Simulation sim = Simulation(bd);

        int nLives = 1;
        if (i == 2) nLives = 6;

        sim.run(nLives);
        std::cout << sim.result << std::endl;
    }
}

int main() {
    // Run all solutions
    solve();
}

```
