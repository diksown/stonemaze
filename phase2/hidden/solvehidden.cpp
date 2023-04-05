#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

#define db(...)                              \
    do {                                     \
        std::cout << #__VA_ARGS__ << " => "; \
        print_debug(__VA_ARGS__);            \
    } while (0)

// Helper function to print variables with different types
template <typename T>
void print_debug(const T &t) {
    std::cout << t << std::endl;
}

template <typename T, typename... Args>
void print_debug(const T &t, const Args &...args) {
    std::cout << t << ", ";
    print_debug(args...);
}

typedef vector<string> board;

int foundCount = 0;
int n, m;
vector<pair<int, int>> order;
vector<int> firstIt(1000);
string sol = "";
ll ct = 0;

void dfs(board b, vector<vector<char>> &visited, int l, int c, char color) {
    if (l < 0 || l >= n || c < 0 || c >= m) return;
    if (b[l][c] != 'x' && b[l][c] != color) return;
    if (visited[l][c]) return;
    visited[l][c] = 1;
    dfs(b, visited, l - 1, c, color);
    dfs(b, visited, l + 1, c, color);
    dfs(b, visited, l, c - 1, color);
    dfs(b, visited, l, c + 1, color);
}

bool connected(board &b, char color) {
    vector<vector<char>> visited(n, vector<char>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[i][j] == color) {
                dfs(b, visited, i, j, color);
                goto end;
            }
        }
    }
end:
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[i][j] == color && !visited[i][j]) return false;
        }
    }
    return true;
}

bool connected(board &b) { return connected(b, '0') && connected(b, '1'); }

// Reasons for invalidity:
// 1. There is a 2x2 square made of 0's or 1's
// 2. There is block of isolated 0's or 1's
bool valid(board &b) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (b[i][j] == 'x') continue;
            if (b[i][j] == b[i][j + 1] && b[i][j] == b[i + 1][j] &&
                b[i][j] == b[i + 1][j + 1])
                return false;
        }
    }
    if (!connected(b)) return false;
    return true;
}

// A function that counts the number of mines in the 8 adjacent cells
int count_neighbours(board &b, int l, int c) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            if (l + i < 0 || l + i >= n || c + j < 0 || c + j >= m) continue;
            if (b[l + i][c + j] == 'x') count++;
        }
    }
    return count;
}

void show(board &b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << b[i][j];
        }
        cout << endl;
    }
    cout << "=========" << endl;
}

void showChar(board b, int l, int c) {
    b[l][c] = '#';
    show(b);
}

void solve(board &b, int it = 0) {
    if (!valid(b)) return;
    if (firstIt[it] == 0) {
        firstIt[it] = 1;
        cout << "it: " << it << endl;
        show(b);
    }
    if (it == order.size()) {
        cout << "found!!!!" << endl;
        foundCount++;
        show(b);
        return;
    }
    int l = order[it].first, c = order[it].second;
    b[l][c] = '1';
    sol += '1';
    solve(b, it + 1);
    sol.pop_back();
    b[l][c] = '0';
    sol += '0';
    solve(b, it + 1);
    sol.pop_back();
    b[l][c] = 'x';
}

signed main() {
    fastcin;
    board b = {"xxxxxx1xxx",  //
               "x0xxx01xx1",  //
               "xxx1xxxx0x",  //
               "x11xx1x1xx",  //
               "1xxxx0xx1x",  //
               "xxx1xxx10x",  //
               "x1xxxx11xx",  //
               "1xxxxxxx1x",  //
               "xx1xx1x11x",  //
               "x1xx1xxxxx"};
    n = b.size();
    m = b[0].size();
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[i][j] != 'x') continue;
            int count = count_neighbours(b, i, j);
            pq.push({-(i * n + j), {i, j}});
        }
    }

    while (!pq.empty()) {
        pair<int, pair<int, int>> pqtop = pq.top();
        pair<int, int> p = pqtop.second;
        pq.pop();
        int l = p.first, c = p.second;
        // showChar(b, l, c);
        order.pb({l, c});
    }

    solve(b);

    // found!!
    // 1111111111
    // 1000001001
    // 1011011101
    // 1110010100
    // 1011000110
    // 1001010100
    // 1101011110
    // 1000000010
    // 1010110110
    // 1111100000

    cout << foundCount << endl;
}