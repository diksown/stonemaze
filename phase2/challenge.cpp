#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

#define BOARD_SIZE 2000

struct Coord {
    int lin, col;

    Coord(){};

    Coord(int lin_, int col_) {
        lin = lin_;
        col = col_;
    }

    Coord(pair<int, int> coord) {
        lin = coord.first;
        col = coord.second;
    }

    Coord operator+(const Coord& other) const {
        return Coord(lin + other.lin, col + other.col);
    }
};

struct Board {
    vector<bitset<BOARD_SIZE>> board;

    Coord playerPos;

    Board(){};

    Board(vector<bitset<BOARD_SIZE>>& initialBoard) { board = initialBoard; }

    bool valid(Coord co) {
        return co.lin >= 0 && co.lin < BOARD_SIZE && co.col >= 0 &&
               co.col < BOARD_SIZE;
    }

    vector<Coord> vNeighbours(Coord co) {
        vector<Coord> neighs;
        for (auto dl : {-1, 0, 1}) {
            for (auto dc : {-1, 0, 1}) {
                if (dl == 0 && dc == 0) continue;
                Coord neigh = Coord(dl, dc) + co;
                if (valid(co)) neighs.pb(co);
            }
        }
        return neighs;
    }
};

Board readBoardFromFile(string filename) {
    // Open the input file for reading
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Failed to open input file" << endl;
        exit(1);
    }

    // Read the input values into a vector of bitsets
    vector<bitset<BOARD_SIZE>> inputValues;
    for (int i = 0; i < BOARD_SIZE; i++) {
        bitset<BOARD_SIZE> row;
        for (int j = 0; j < BOARD_SIZE; j++) {
            int bitValue;
            inputFile >> bitValue;
            row[j] = bitValue;
        }
        inputValues.push_back(row);
    }

    return Board(inputValues);
}

signed main() {
    fastcin;
    Board b = readBoardFromFile("input/input1.txt");
    int onect = 0, zeroct = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (b.board[i][j] == 0)
                zeroct++;
            else
                onect++;
        }
    }
    cout << onect << " " << zeroct << endl;
}