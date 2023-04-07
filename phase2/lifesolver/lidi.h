#ifndef LIDI_H
#define LIDI_H

#include "board.h"

typedef char lidi;

#define LIDI_X 0b000
#define LIDI_U 0b001
#define LIDI_R 0b010
#define LIDI_D 0b011
#define LIDI_L 0b100

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
    bool reachedEnd();

   private:
    void getNextParticle(int l, int c, LidiBoard& newLidiBoard, bool isGreen);
    void initLidiBoard(int nLines, int nCols);
};

std::ostream& operator<<(std::ostream& o, LidiBoard& lidib);

int getLife(lidi particle);

std::pair<int, int> unpackLidi(lidi particle);

#endif  // LIDI_H