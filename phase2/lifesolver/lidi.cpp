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

#define LIDI_X 0b000
#define LIDI_U 0b001
#define LIDI_R 0b010
#define LIDI_D 0b011
#define LIDI_L 0b100

std::vector<std::vector<lidi>> createMatrixLidi(int n, int m) {
    std::vector<std::vector<lidi>> matrix =
        std::vector<std::vector<lidi>>(n, std::vector<lidi>(m));
    return matrix;
}

LidiBoard::LidiBoard(int nLines, int nCols) {
    n = nLines;
    m = nCols;
    board = createMatrixLidi(n, m);
}

LidiBoard::LidiBoard(const Board& initialBoard) {
    n = initialBoard.n;
    m = initialBoard.m;
    board = createMatrixLidi(n, m);
}

std::pair<int, int> unpackLidi(lidi particle) {
    int life = (particle >> 3) & 0b111;
    int direction = particle & 0b111;
    return {life, direction};
}

lidi packLidi(std::pair<int, int> particle) {
    int life = particle.first;
    int direction = particle.second;
    return (lidi)((life << 3) | direction);
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
            NewLidiBoard.board[nl][nc] = packLidi({life, dir + 1});
        }
    }
}

LidiBoard LidiBoard::getNextLidiBoard(Board& futureBoard) {
    // Initialize everything with zeros, which 0X (0 lives, direction X)
    LidiBoard NewLidiBoard(futureBoard.n, futureBoard.m);
    for (int l = 0; l < futureBoard.n; l++) {
        for (int c = 0; c < futureBoard.m; c++) {
            propagate(l, c, NewLidiBoard, futureBoard.board[l][c]);
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

std::vector<std::string> LidiBoard::repr() {
    std::vector<std::string> repr;
    for (int l = 0; l < n; l++) {
        std::string line;
        for (int c = 0; c < m; c++) {
            int life, direction;
            std::tie(life, direction) = unpackLidi(board[l][c]);
            line += std::to_string(life) + getDirectionChar(direction) + " ";
        }
        repr.push_back(line);
    }
    return repr;
}

void LidiBoard::print() {
    for (auto line : repr()) {
        std::cout << line << std::endl;
    }
}