#ifndef LIDI_H
#define LIDI_H

#include "board.h"

typedef char lidi;

struct LidiBoard {
    std::vector<std::vector<char>> board;
    int n, m;
    LidiBoard(int n, int m);
    LidiBoard(const Board& board);
    LidiBoard getNextLidiBoard(Board& board);
    std::vector<std::string> repr();
    void print();

   private:
    void propagate(int l, int c, LidiBoard& NewLidiBoard, bool isGreen);
};

#endif  // LIDI_H