#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

#define WHITE 0
#define GREEN 1

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

const vector<string> BOARD11 = {
    "00000000",  //
    "00001000",  //
    "00101100",  //
    "01100110",  //
    "00101100",  //
    "00001000",  //
    "00000000",  //
};

struct Board {
    bool** board;

    int n, m;

    Board(int n, int m) {
        this->n = n;
        this->m = m;
        board = new bool*[n];
        for (int i = 0; i < n; i++) {
            board[i] = new bool[m];
            for (int j = 0; j < m; j++) {
                board[i][j] = false;
            }
        }
    }

    ~Board() {
        for (int i = 0; i < n; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    // returns true if the cell (l, c) is inside the board
    bool isValid(int l, int c) { return l >= 0 && l < n && c >= 0 && c < m; }

    // returns the amount of neighbours of the cell (l, c) that are alive
    int countNeighbours(int l, int c) {
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
    }

    // returns true if the cell (l, c) should change its state
    bool shouldChange(int l, int c, bool firstPhase = false) {
        int count = countNeighbours(l, c);
        // the first sigmageek challenge
        // had a different ruleset
        if (board[l][c] == WHITE) {
            return count > 1 && count < (firstPhase ? 4 : 5);
        } else if (board[l][c] == GREEN) {
            return !(count > 3 && count < (firstPhase ? 7 : 6));
        }

        // panic, boolean is not 0 or 1
        exit(1);
        return false;
    }

    void update(bool firstPhase = false) {
        bool** newBoard = createMatrixBool(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (shouldChange(i, j, firstPhase)) {
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
    }

    static Board simpleBoard() {
        int n = BOARD11.size();
        int m = BOARD11[0].size();
        Board board(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                board.board[i][j] = BOARD11[i][j] == '1';
            }
        }
        return board;
    }

    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << (board[i][j] == WHITE ? " " : "█");
            }
            cout << endl;
        }
    }

    void show() {}
};

int main() {
    fastcin;
    // testing the board
    Board board = Board::simpleBoard();
    board.print();
    for (int i = 0; i < 100; i++) {
        // take a nap
        this_thread::sleep_for(chrono::milliseconds(10));
        board.update(true);
        board.print();
        cout << endl;
    }
}