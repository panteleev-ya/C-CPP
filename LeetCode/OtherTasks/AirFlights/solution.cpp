#include <iostream>
#include <vector>

using namespace std;

vector<bool> visited;
vector<vector<bool>> flyable;

void fly(int city);
bool everything_is_reachable();

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int min_tank_size = 1000000001;
    int max_tank_size = 0;

    int n;
    cin >> n;
    vector<vector<int>> distances(n, vector<int>(n));
    int distance;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distance;
            distances[i][j] = distance;
            min_tank_size = min(min_tank_size, distance);
            max_tank_size = max(max_tank_size, distance);
        }
    }

    // Set visited and flyable to start values
    visited = vector<bool>(n, false);
    flyable = vector<vector<bool>>(n, vector<bool>(n, false));

    // Binary searching for the tank size
    while (min_tank_size < max_tank_size) {
        int midSize = (min_tank_size + max_tank_size) / 2;

        // Checking ability to fly from i to j directly
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distances[i][j] <= midSize) {
                    flyable[i][j] = true;
                } else {
                    flyable[i][j] = false;
                }
            }
        }

        // If the tank size is enough to fly everywhere,
        // we try to make it lower, otherwise we make it higher
        if (everything_is_reachable()) {
            max_tank_size = midSize;
        } else {
            min_tank_size = midSize + 1;
        }
    }

    cout << min_tank_size << "\n";
    return 0;
}

void fly(int city) {
    visited[city] = true;
    for (int next_city = 0; next_city < visited.size(); next_city++) {
        if (!visited[next_city] && flyable[city][next_city]) {
            fly(next_city);
        }
    }
}

void flyBack(int city) {
    visited[city] = true;
    for (int next_city = 0; next_city < visited.size(); next_city++) {
        if (!visited[next_city] && flyable[next_city][city]) {
            flyBack(next_city);
        }
    }
}

bool everything_is_reachable() {
    // Set everything to unvisited
    for (auto &&cityVisited: visited) {
        cityVisited = false;
    }

    // Flying everywhere we can
    fly(0);

    // Checking if we visited everything
    for (auto && city_visited : visited) {
        if (!city_visited) {
            return false;
        }
    }

    // Set everything back to unvisited
    for (auto &&cityVisited: visited) {
        cityVisited = false;
    }

    // Flying back
    flyBack(0);

    // Checking if we visited everything
    for (auto && city_visited : visited) {
        if (!city_visited) {
            return false;
        }
    }

    return true;
}
