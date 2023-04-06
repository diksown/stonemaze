#include <bits/stdc++.h>

#include "board.h"
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

int main() {
    fastcin;
    Board board = Board::randomBoard();
    for (int i = 0; i < 10; i++) {
        // take a nap
        this_thread::sleep_for(chrono::milliseconds(10));
        board = Board::randomBoard();
        board.print();
        cout << endl;
    }
}