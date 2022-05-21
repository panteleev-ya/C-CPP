#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> isLeftPart;

void dfs(int from, bool vertexColor, bool &conflicting);

int main() {
    int n, m;
    cin >> n >> m;

    graph = vector<vector<int>>(n);
    isLeftPart = vector<bool>(n, false);

    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }

    bool conflicting = true;
    for (int i = 0; i < n; i++)
        if (isLeftPart[i] == false) {
            dfs(i, false, conflicting);
            if (!conflicting) {
                cout << "NO" << "\n";
                return 0;
            }
        }
    cout << "YES" << "\n";
    return 0;
}

void dfs(int from, bool vertexColor, bool &conflicting) {
    isLeftPart[from] = vertexColor;
    for (int to: graph[from]) {
        if (isLeftPart[to] == false)
            dfs(to, !vertexColor, conflicting);
        else if (isLeftPart[to] == vertexColor) {
            conflicting = false;
            return;
        }
    }
}
