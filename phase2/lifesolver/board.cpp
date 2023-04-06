#include "board.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define WHITE 0
#define GREEN 1

bool** createMatrixBool(int n, int m) {
    bool** matrix = new bool*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new bool[m];
    }
    return matrix;
}

void deleteMatrixBool(bool** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
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

bool** board;

int n, m;

Board::Board(int n, int m) {
    this->n = n;
    this->m = m;
    board = new bool*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new bool[m];
        for (int j = 0; j < m; j++) {
            board[i][j] = false;
        }
    }
};

Board::~Board() {
    for (int i = 0; i < n; i++) {
        delete[] board[i];
    }
    delete[] board;
};

// returns true if the cell (l, c) is inside the board
bool Board::isValid(int l, int c) { return l >= 0 && l < n && c >= 0 && c < m; };

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

void Board::update(std::string mode = "second_phase") {
    bool** newBoard = createMatrixBool(n, m);
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

    deleteMatrixBool(board, n);
    board = newBoard;
};

Board Board::simpleBoard() {
    int n = BOARD11.size();
    int m = BOARD11[0].size();
    Board board(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            board.board[i][j] = BOARD11[i][j] == '1';
        }
    }
    return board;
};

void Board::print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << (board[i][j] == WHITE ? " " : "█");
        }
        std::cout << std::endl;
    }
};

void show(){};
