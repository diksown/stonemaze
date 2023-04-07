#include "lidi.h"

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

/*
 * lidi means "(li)fe (di)rection"
 * it is a structure that will hold the amount of life and the direction of the
 * parent of the cell. it has the following structure:
 * 00 [000] [000]
 * ^  ^     ^
 * |  |     |
 * |  |     +-- direction of the parent of the cell (01234 => URDLX)
 * |  +-------- amount of life of the cell (0-6, 0 means dead)
 * +----------- unused
 */

typedef char lidi;

#define LIDI_U 0b000
#define LIDI_R 0b001
#define LIDI_D 0b010
#define LIDI_L 0b011
#define LIDI_X 0b100

std::vector<std::vector<lidi>> createMatrixlidi(int n, int m) {
    std::vector<std::vector<lidi>> matrix =
        std::vector<std::vector<lidi>>(n, std::vector<lidi>(m, false));
    return matrix;
}

LidiBoard::LidiBoard(int n, int m) {
    this->n = n;
    this->m = m;
    this->board = createMatrixlidi(n, m);
}

LidiBoard::LidiBoard(const Board& board) {
    this->n = board.n;
    this->m = board.m;
    this->board = createMatrixlidi(n, m);
}

std::pair<int, int> unpackLidi(lidi particle) {
    int life = (particle >> 3) & 0b111;
    int direction = particle & 0b111;
    return {life, direction};
}

lidi packLidi(std::pair<int, int> particle) {
    int life = particle.first;
    char direction = particle.second;
    return (life << 3) | direction;
}

int getLife(lidi particle) { return (particle >> 3) & 0b111; }

bool isOutside(int l, int c, int n, int m) {
    return l < 0 || l >= n || c < 0 || c >= m;
}

void LidiBoard::propagate(int l, int c, LidiBoard& NewLidiBoard, bool isGreen) {
    // Check the life of the cell
    int life = getLife(board[l][c]);
    if (life == 0) return;

    // If the cell is green, it will lose life
    if (isGreen) life--;
    if (life == 0) return;

    // U, R, D, L
    int dl[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    // Propagate the particle to the neighbours
    for (int dir = 0; dir < 4; dir++) {
        int nl = l + dl[dir];
        int nc = c + dc[dir];
        if (isOutside(nl, nc, n, m)) continue;
        lidi particle = NewLidiBoard.board[nl][nc];
        int nlife = getLife(particle);
        if (life > nlife) {
            NewLidiBoard.board[nl][nc] = packLidi({life, dir});
        }
    }
}

LidiBoard LidiBoard::getNextLidiBoard(Board& board) {
    // Initialize everything with zeros, which 0X (0 lives, direction X)
    LidiBoard NewLidiBoard(board.n, board.m);
    for (int l = 0; l < board.n; l++) {
        for (int c = 0; c < board.m; c++) {
            propagate(l, c, NewLidiBoard, board.board[l][c]);
        }
    }
    return NewLidiBoard;
}

char getDirectionChar(int direction) {
    std::map<int, char> directionChar = {{LIDI_U, 'U'},
                                         {LIDI_R, 'R'},
                                         {LIDI_D, 'D'},
                                         {LIDI_L, 'L'},
                                         {LIDI_X, 'X'}};
    return directionChar[direction];
}

void LidiBoard::print() {
    for (int l = 0; l < n; l++) {
        for (int c = 0; c < m; c++) {
            int life, direction;
            std::tie(life, direction) = unpackLidi(board[l][c]);
            std::cout << life << getDirectionChar(direction) << " ";
        }
        std::cout << std::endl;
    }
}