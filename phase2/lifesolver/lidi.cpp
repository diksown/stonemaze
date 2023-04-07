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

std::vector<std::vector<lidi>> createMatrixLidi(int n, int m) {
    std::vector<std::vector<lidi>> matrix =
        std::vector<std::vector<lidi>>(n, std::vector<lidi>(m));
    return matrix;
}

void LidiBoard::initLidiBoard(int nLines, int nCols) {
    n = nLines;
    m = nCols;
    board = createMatrixLidi(n, m);
}

LidiBoard::LidiBoard(int nLines, int nCols) { initLidiBoard(nLines, nCols); }

LidiBoard::LidiBoard(const Board& initialBoard) {
    initLidiBoard(initialBoard.n, initialBoard.m);
}

LidiBoard LidiBoard::getLidiBoardWithOneParticle(int nLines, int nCols,
                                                 int lives,
                                                 std::pair<int, int> pos) {
    LidiBoard lidiBoard = LidiBoard(nLines, nCols);
    lidiBoard.board[pos.first][pos.second] = packLidi({lives, LIDI_X});
    return lidiBoard;
}

LidiBoard LidiBoard::getLidiBoardWithOneParticle(const Board& board, int lives,
                                                 std::pair<int, int> pos) {
    return getLidiBoardWithOneParticle(board.n, board.m, lives, pos);
}

bool LidiBoard::reachedEnd() {
    int life = getLife(board[n - 1][m - 1]);
    return life > 0;
}

bool LidiBoard::isDead() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int life = getLife(board[i][j]);
            if (life > 0) return false;
        }
    }
    return true;
}

int getLife(lidi particle) { return (particle >> 3) & 0b111; }

bool isOutside(int l, int c, int n, int m) {
    return l < 0 || l >= n || c < 0 || c >= m;
}

// Will set (l, c) particle in newLidiBoard to the best particle
// And how we reached it
void LidiBoard::getNextParticle(int l, int c, LidiBoard& newLidiBoard,
                                bool isGreen) {
    // U, R, D, L
    int dl[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    int life = getLife(newLidiBoard.board[l][c]);

    // Get the best neighbour
    for (int dir = 0; dir < 4; dir++) {
        int nl = l + dl[dir];
        int nc = c + dc[dir];
        if (isOutside(nl, nc, n, m)) continue;

        lidi neighbour = board[nl][nc];
        int neighbourLife = getLife(neighbour);

        // If the cell is green, it will lose life
        if (isGreen) neighbourLife--;

        // If the neighbour is better, update the newLidiBoard
        if (neighbourLife > life) {
            life = neighbourLife;
            newLidiBoard.board[l][c] = packLidi({life, dir + 1});
        }
    }
}

LidiBoard LidiBoard::getNextLidiBoard(Board& futureBoard) {
    // Initialize everything with zeros, which 0X (0 lives, direction X)
    LidiBoard newLidiBoard(futureBoard.n, futureBoard.m);
    for (int l = 0; l < futureBoard.n; l++) {
        for (int c = 0; c < futureBoard.m; c++) {
            getNextParticle(l, c, newLidiBoard, futureBoard.board[l][c]);
        }
    }
    return newLidiBoard;
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

std::ostream& operator<<(std::ostream& o, LidiBoard& lidib) {
    for (auto line : lidib.repr()) {
        std::cout << line << '\n';
    }
    std::cout << std::flush;
    return o;
}
