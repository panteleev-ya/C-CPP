#include <iostream>
#include <queue>
#include <stack>

using namespace std;

const int intmax = 2147483647;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int start_x, start_y;
    cin >> start_x >> start_y;
    start_x--;
    start_y--;

    int end_x, end_y;
    cin >> end_x >> end_y;
    end_x--;
    end_y--;

    char worldMap[n][m];
    int distances[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> worldMap[i][j];
            distances[i][j] = intmax;
        }
    }

    // Left, up, right and down steps
    int steps[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    distances[start_x][start_y] = 0;

    // Setting queue of unmarked points, pushing start point
    queue<pair<int, int>> cellsQueue;
    cellsQueue.push(pair<int, int>(start_x, start_y));

    while (!cellsQueue.empty()) {
        pair<int, int> cell = cellsQueue.front();
        cellsQueue.pop();
        int x = cell.first;
        int y = cell.second;

        for (auto & step : steps) {
            // Trying to move to the left, up, right and down
            int step_x = x + step[0];
            int step_y = y + step[1];

            // Is not valid step (step out of bounds)
            if (!(step_x >= 0 && step_x < n && step_y >= 0 && step_y < m)) {
                continue;
            }

            char next_cell_type = worldMap[step_x][step_y];

            // Next cell type is water, so we can't move there
            if (next_cell_type == '#') {
                continue;
            }

            // Getting step cost of time to travel
            int step_cost = 1;
            if (next_cell_type == 'W') {
                step_cost = 2;
            }

            // Checking if it is a better way to get there
            if (distances[step_x][step_y] > distances[x][y] + step_cost) {
                distances[step_x][step_y] = distances[x][y] + step_cost;
                cellsQueue.push(pair<int, int>(step_x, step_y));
            }
        }
    }

    // Can't be reached
    if (distances[end_x][end_y] == intmax) {
        cout << -1 << "\n";
        return 0;
    }

    // Printing result way length
    cout << distances[end_x][end_y] << "\n";

    int x = end_x;
    int y = end_y;
    string step_types = "ESWN";
    stack<char> reversed_way;

    // Building reversed result way
    while (!(x == start_x && y == start_y)) {
        int min_dist = intmax;
        char step_type;
        int next_x, next_y;
        for (int step = 0; step < 4; step++) {
            int step_x = x + steps[step][0];
            int step_y = y + steps[step][1];

            // Is not valid step (step out of bounds)
            if (!(step_x >= 0 && step_x < n && step_y >= 0 && step_y < m)) {
                continue;
            }

            // Finding minimal distance out of every possible step
            if (distances[step_x][step_y] < min_dist) {
                min_dist = distances[step_x][step_y];
                next_x = step_x;
                next_y = step_y;
                step_type = step_types[step];
            }
        }

        x = next_x;
        y = next_y;
        reversed_way.push(step_type);
    }

    // Reversing result way
    string result_way;
    while (!reversed_way.empty()) {
        result_way += reversed_way.top();
        reversed_way.pop();
    }

    // Printing result way
    cout << result_way << "\n";
    return 0;
}
