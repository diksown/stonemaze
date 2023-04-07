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
    void print();

   private:
    void propagate(int l, int c, LidiBoard& NewLidiBoard, bool isGreen);
};

std::vector<std::vector<lidi>> createMatrixLidi(int n, int m);

#endif  // LIDI_H