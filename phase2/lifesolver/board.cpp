#include "board.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define WHITE 0
#define GREEN 1

std::vector<std::vector<bool>> createMatrixBool(int n, int m) {
    std::vector<std::vector<bool>> matrix =
        std::vector<std::vector<bool>>(n, std::vector<bool>(m, false));
    return matrix;
}

const std::vector<std::string> BOARD11 = {
    "00000000",  //
    "00001000",  //
    "00101100",  //
    "01100110",  //
    "00101100",  //
    "00001000",  //
    "00000000",  //
};

Board::Board(int nLines, int nCols) {
    this->n = nLines;
    this->m = nCols;
    this->board = createMatrixBool(nLines, nCols);
};

// returns true if the cell (l, c) is inside the board
bool Board::isValid(int l, int c) {
    return l >= 0 && l < n && c >= 0 && c < m;
};

// returns the amount of neighbours of the cell (l, c) that are alive
int Board::countNeighbours(int l, int c) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (isValid(l + i, c + j) && board[l + i][c + j]) {
                count++;
            }
        }
    }
    return count;
};

// returns true if the cell (l, c) should change its state
bool Board::shouldChange(int l, int c, std::string mode = "second_phase") {
    int count = countNeighbours(l, c);
    // the first sigmageek challenge
    // had a different ruleset
    if (board[l][c] == WHITE) {
        return count > 1 && count < (mode == "first_phase" ? 4 : 5);
    } else if (board[l][c] == GREEN) {
        return !(count > 3 && count < (mode == "first_phase" ? 7 : 6));
    }

    // panic, boolean is not 0 or 1
    exit(1);
    return false;
};

void Board::next(std::string mode) {
    std::vector<std::vector<bool>> newBoard = createMatrixBool(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (shouldChange(i, j, mode)) {
                newBoard[i][j] = !board[i][j];
            } else {
                newBoard[i][j] = board[i][j];
            }
        }
    }

    // the beginning and the end of the board are always white
    // actually yellow, but we can represent it as white
    newBoard[0][0] = WHITE;
    newBoard[n - 1][m - 1] = WHITE;

    board = newBoard;
};

Board Board::simpleBoard() {
    int nLines = (int)BOARD11.size();
    int nCols = (int)BOARD11[0].size();
    Board sb(nLines, nCols);
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nCols; j++) {
            sb.board[i][j] = BOARD11[i][j] == '1';
        }
    }
    return sb;
};

Board Board::randomBoard(int n, int m, int seed) {
    std::srand(seed);
    Board rb(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rb.board[i][j] = std::rand() % 2;
        }
    }
    return rb;
};

std::vector<std::string> Board::repr() {
    std::vector<std::string> repr;
    for (int i = 0; i < n; i++) {
        std::string line = "";
        for (int j = 0; j < m; j++) {
            line += (board[i][j] == WHITE ? "  " : "██");
        }
        repr.push_back(line);
    }
    return repr;
};

std::ostream& operator<<(std::ostream& o, Board& board) {
    for (auto line : board.repr()) {
        o << line << '\n';
    }
    std::cout << std::flush;
    return o;
}