#include <bits/stdc++.h>

#include "board.h"
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

/*
 * lidi means "(li)fe (di)rection"
 * it is a structure that will hold the amount of life and the direction of the
 * parent of the cell. it has the following structure:
 * 00 [000] [000]
 * ^  ^     ^
 * |  |     |
 * |  |     +-- direction of the parent of the cell (01234 => XURDL)
 * |  +-------- amount of life of the cell (0-6, 0 means dead)
 * +----------- unused
 */

typedef char lidi;

lidi** createMatrixLidi(int n, int m) {
    lidi** matrix = new lidi*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new lidi[m];
    }
    return matrix;
}

void deleteMatrixLidi(lidi** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    fastcin;
    // testing the board
    Board board = Board::simpleBoard();
    board.print();
    for (int i = 0; i < 100; i++) {
        // take a nap
        this_thread::sleep_for(chrono::milliseconds(10));
        board.update("first_phase");
        board.print();
        cout << endl;
    }
}