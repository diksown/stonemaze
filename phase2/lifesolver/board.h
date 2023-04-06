#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

struct Board {
    std::vector<std::vector<bool>> board;
    int n, m;
    Board(int n, int m);
    void update(std::string mode = "second_phase");
    static Board simpleBoard();
    void print();
    void show();
    static Board randomBoard();

   private:
    bool isValid(int l, int c);
    int countNeighbours(int l, int c);
    bool shouldChange(int l, int c, std::string mode);
};

#endif  // BOARD_H