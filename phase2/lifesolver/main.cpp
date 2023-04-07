#include <iostream>

#include "board.h"
#include "lidi.h"
#include "utils.h"

int main() {
    Board board = Board::randomBoard();
    LidiBoard lidiBoard = LidiBoard(board);
    std::vector<LidiBoard> lidiBoards;

    for (int i = 0; i < 10; i++) {
        board.next();
        LidiBoard newLidiBoard = lidiBoard.getNextLidiBoard(board);
        lidiBoards.push_back(newLidiBoard);
        board.print();
        std::cout << std::endl;
        newLidiBoard.print();
        std::cout << std::endl;
    }
}