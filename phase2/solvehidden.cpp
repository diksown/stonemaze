#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fastcin cin.tie(0)->sync_with_stdio(0);

typedef vector<string> board;

int n, m;
vector<pair<int, int>> order;

void dfs(board b, vector<vector<char>> &visited, int l, int c, char color) {
    if (l < 0 || l >= n || c < 0 || c >= m) return;
    if (b[l][c] != 'x' && b[l][c] != color) return;
    if (visited[l][c]) return;
    if (b[l][c] != color) return;
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

void solve(board &b, int it = 0) {
    if (!valid(b)) return;
    if (it == order.size()) {
        show(b);
        return;
    }
    int l = order[it].first, c = order[it].second;
    b[l][c] = '0';
    solve(b, it + 1);
    b[l][c] = '1';
    solve(b, it + 1);
    b[l][c] = 'x';
}

signed main() {
    fastcin;
    board b = {
        "x0xxx01xx1", "xxx1xxxx0x", "x11xx1x1xx", "1xxxx0xx1x", "xxx1xxx10x",
        "x1xxxx11xx", "1xxxxxxx1x", "xx1xx1x11x", "x1xx1xxxxx",
    };
    n = b.size();
    m = b[0].size();
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[i][j] != 'x') continue;
            int count = count_neighbours(b, i, j);
            pq.push({-count, {i, j}});
        }
    }

    while (!pq.empty()) {
        pair<int, pair<int, int>> pqtop = pq.top();
        pair<int, int> p = pqtop.second;
        pq.pop();
        int l = p.first, c = p.second;
        order.pb({l, c});
    }

    solve(b);
}