#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

#define BOARD_SIZE 85
#define WHITE 0
#define GREEN 1

void err(string errMsg) {
    cerr << errMsg << endl;
    exit(1);
}

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

    bool operator==(const Coord& other) const {
        return lin == other.lin and col == other.col;
    }

    bool operator!=(const Coord& other) const { return !operator==(other); }
};

struct Board {
    vector<bitset<BOARD_SIZE>> board;

    Coord playerPos;

    Board(){};

    Board(vector<bitset<BOARD_SIZE>>& initialBoard) { board = initialBoard; }

    bool valid(Coord co) {
        return co.lin >= 0 and co.lin < BOARD_SIZE and co.col >= 0 and
               co.col < BOARD_SIZE;
    }

    vector<Coord> vNeighbours(Coord co) {
        vector<Coord> neighs;
        for (auto dl : {-1, 0, 1}) {
            for (auto dc : {-1, 0, 1}) {
                if (dl == 0 and dc == 0) continue;
                Coord neigh = Coord(dl, dc) + co;
                if (valid(co)) neighs.pb(co);
            }
        }
        return neighs;
    }

    vector<Coord> eNeighbours(Coord co) {
        vector<Coord> neighs;
        for (auto coord :
             vector<pair<int, int>>{{0, -1}, {0, 1}, {1, 0}, {-1, 0}}) {
            int dl, dc;
            tie(dl, dc) = coord;
            Coord neigh = Coord(dl, dc) + co;
            if (valid(co)) neighs.pb(co);
        }
        return neighs;
    }

    bool isYellow(Coord co) {
        return co == Coord(0, 0) or co == Coord(BOARD_SIZE - 1, BOARD_SIZE - 1);
    }

    bool isGreen(Coord co) {
        if (!valid(co)) err("Can't check invalid coord");
        if (isYellow(co)) return false;
        return board[co.lin][co.col] == GREEN;
    }

    bool isWhite(Coord co) {
        if (!valid(co)) err("Can't check invalid coord");
        if (isYellow(co)) return false;
        return board[co.lin][co.col] == WHITE;
    }

    map<bool, int> countNeighbourColor(Coord co) {
        map<bool, int> colorCount;
        colorCount[WHITE] = 0;
        colorCount[GREEN] = 0;
        for (auto coord : vNeighbours(co)) {
            if (isWhite(coord)) colorCount[WHITE]++;
            if (isGreen(coord)) colorCount[GREEN]++;
        }
        return colorCount;
    }

    bool shouldChange(Coord co) {
        if (!valid(co)) err("Can't check invalid coord");
        if (isYellow(co)) return false;
        map<bool, int> colorCount = countNeighbourColor(co);
        // White cells turn green if they have a number of green adjacent cells
        // greater than 1 and less than 5. Otherwise, they remain white.
        if (isWhite(co)) {
            return colorCount[GREEN] > 1 and colorCount[GREEN] < 5;
        }
        // Green cells remain green if they have a number of green adjacent
        // cells greater than 3 and less than 6. Otherwise, they become white.
        if (isGreen(co)) {
            return !(colorCount[GREEN] > 3 and colorCount[GREEN] < 6);
        }
    }

    void next() {
        vector<bitset<BOARD_SIZE>> newBoard = board;
        for (int lin = 0; lin < BOARD_SIZE; lin++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (shouldChange(Coord(lin, col)))
                    newBoard[lin][col] = !newBoard[lin][col];
            }
        }
    }

    void show() {
        string greenCell = u8"\u2588\u2588";
        string whiteCell = u8"\u2591\u2591";
        string yellowCell = u8"\u25A0\u25A0";
        for (int lin = 0; lin < BOARD_SIZE; lin++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (isGreen(Coord(lin, col)))
                    cout << greenCell;
                else if (isWhite(Coord(lin, col)))
                    cout << whiteCell;
                else if (isYellow(Coord(lin, col)))
                    cout << yellowCell;
            }
            cout << endl;
        }
        cout << endl;
    }
};

Board readBoardFromFile(string filename) {
    // Open the input file for reading
    ifstream inputFile(filename);
    if (!inputFile) err("Failed to open input file");

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

void sleep(int x) { this_thread::sleep_for(std::chrono::milliseconds(x)); }

signed main() {
    fastcin;
    Board b = readBoardFromFile("input/phase1input2.txt");
    while (true) {
        sleep(1000);
        b.next();
        b.show();
    }
}