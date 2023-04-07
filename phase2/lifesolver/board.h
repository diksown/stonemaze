#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

struct Board {
    std::vector<std::vector<bool>> board;
    int n, m;
    Board(int nLines, int nCols);
    void next(std::string mode = "second_phase");
    static Board simpleBoard();
    void print();
    std::vector<std::string> repr();
    static Board randomBoard(int nLines = 20, int nCols = 20);

   private:
    bool isValid(int l, int c);
    int countNeighbours(int l, int c);
    bool shouldChange(int l, int c, std::string mode);
};

std::ostream& operator<<(std::ostream& o, Board& board);

#endif  // BOARD_H