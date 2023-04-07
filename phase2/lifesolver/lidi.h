#ifndef LIDI_H
#define LIDI_H

#include "board.h"

typedef char lidi;

struct LidiBoard {
    std::vector<std::vector<char>> board;
    int n, m;

    LidiBoard(int n, int m);
    static LidiBoard getLidiBoardWithOneParticle(
        int nLines, int nCols, int lives = 1, std::pair<int, int> pos = {0, 0});
    static LidiBoard getLidiBoardWithOneParticle(
        const Board& board, int lives = 1, std::pair<int, int> pos = {0, 0});
    LidiBoard(const Board& board);
    LidiBoard getNextLidiBoard(Board& board);
    std::vector<std::string> repr();

   private:
    void propagate(int l, int c, LidiBoard& NewLidiBoard, bool isGreen);
    void initLidiBoard(int nLines, int nCols);
};

std::ostream& operator<<(std::ostream& o, LidiBoard& lidib);

#endif  // LIDI_H