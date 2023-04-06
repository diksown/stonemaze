#ifndef BOARD_H
#define BOARD_H

#include <string>

struct Board {
    bool** board;

    int n, m;

    Board(int n, int m);
    ~Board();
    void update(std::string mode);
    static Board simpleBoard();
    void print();

   private:
    bool isValid(int l, int c);
    int countNeighbours(int l, int c);
    bool shouldChange(int l, int c, std::string mode);
};

#endif  // BOARD_H