#include <iostream>

#include "board.h"
#include "lidi.h"
#include "utils.h"

struct Foo {
    std::vector<std::vector<char>> bar;
    Foo(int n, int m) {
        bar = std::vector<std::vector<char>>(n, std::vector<char>(m));
    }
};

int main() {
    // Foo bar(10, 10);
    // Foo baz(10, 10);
    std::vector<std::vector<char>>(10);
    std::vector<std::vector<char>>(10, std::vector<char>(10));
    // int n = 10, m = 10;
    // std::vector<std::vector<lidi>> matrix =
    //     std::vector<std::vector<lidi>>(n, std::vector<lidi>(m));
    // LidiBoard l(n, m);
    // Board board = Board::randomBoard();
    // LidiBoard lidiBoard = LidiBoard(board);
    // std::vector<LidiBoard> lidiBoards;

    // for (int i = 0; i < 10; i++) {
    //     board.next();
    //     LidiBoard newLidiBoard = lidiBoard.getNextLidiBoard(board);
    //     lidiBoards.push_back(newLidiBoard);
    //     board.print();
    //     std::cout << std::endl;
    //     newLidiBoard.print();
    //     std::cout << std::endl;
    // }
}