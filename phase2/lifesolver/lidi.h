#ifndef LIDI_H
#define LIDI_H

#include "board.h"

typedef char lidi;

struct LidiBoard {
    std::vector<std::vector<char>> board;
    int n, m;

    LidiBoard(int n, int m, int lives = 1);
    LidiBoard(const Board& board, int lives = 1);
    LidiBoard getNextLidiBoard(Board& board);
    std::vector<std::string> repr();
    void print();

   private:
    void propagate(int l, int c, LidiBoard& NewLidiBoard, bool isGreen);
    void initLidiBoard(int nLines, int nCols, int lives);
};

std::ostream& operator<<(std::ostream& o, LidiBoard& lidib);

#endif  // LIDI_H