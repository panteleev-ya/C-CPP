#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "queue"

#define MAX_INT 2147483647

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::pair;
using std::map;
using std::queue;


class CivilizationField {
public:
    explicit CivilizationField(vector <vector <char>> field);
    void findPlayerWay(pair<int, int> start, pair<int, int> end, int* pathLength, string* path);
private:
    static map<char, int> _costs;
    vector <vector <char>> _field;
    int _field_height;
    int _field_width;
    vector <vector <int>> _used;
    vector<vector<int>> _distances;
};

map<char, int> CivilizationField::_costs = {
        pair<char, int>('.', 1),
        pair<char, int>('W', 2),
        pair<char, int>('#', -1)
};

CivilizationField::CivilizationField(vector<vector<char>> field) {
    this->_field = field;
    this->_field_height = (int) field.size();
    this->_field_width = (int) field[0].size();

    this->_used = vector<vector<int>>(this->_field_height, vector<int>(this->_field_width, 0));
    this->_distances = vector<vector<int>>(this->_field_height, vector<int>(this->_field_width, MAX_INT));

    // Marking unreachable elements as reached
    for (int i = 0; i < this->_field_height; i++) {
        for (int j = 0; j < this->_field_width; j++) {
            if (_costs[this->_field[i][j]] == -1) {
                _used[i][j] = -1;
            }
        }
    }
}

void CivilizationField::findPlayerWay(pair<int, int> start, pair<int, int> end, int* pathLength, string* path) {
    int x0 = start.first;
    int y0 = start.second;

    int x1 = end.first;
    int y1 = end.second;

    // Setting distance from start to itself as 0
    // other distances now are "infinities" (means they are unreached)
    _distances[x0][y0] = 0;

    // Setting queue of unmarked points, pushing start point
    queue<pair<int, int>> plan;
    plan.push(start);

    pair<int, int> current = pair<int, int>(-1, -1);

    // While there is at least one unmarked reachable point -> reaching them
    while (!plan.empty()) {
        // Getting a point
        current = plan.front();
        plan.pop();
        if (current.first == end.first && current.second == end.second) {
            if (plan.empty()) {
                break;
            }
            current = plan.front();
            plan.pop();
        }
        int x = current.first;
        int y = current.second;


        int distance;

        // Adding his neighbors to the plan (if not reached yet) and counting new min distance from start to them
        // Up
        if (x - 1 >= 0) {
            distance = _distances[x][y] + _costs[_field[x - 1][y]];
            if (_used[x - 1][y] != -1 && _distances[x - 1][y] > distance) {
                _distances[x - 1][y] = distance;
                plan.push(pair<int, int>(x - 1, y));
            }
        }
        // Down
        if (x + 1 < this->_field_height) {
            distance = _distances[x][y] + _costs[_field[x + 1][y]];
            if (_used[x + 1][y] != -1 && _distances[x + 1][y] > distance) {
                _distances[x + 1][y] = distance;
                plan.push(pair<int, int>(x + 1, y));
            }
        }
        // Left
        if (y - 1 >= 0) {
            distance = _distances[x][y] + _costs[_field[x][y - 1]];
            if (_used[x][y - 1] != -1 && _distances[x][y - 1] > distance) {
                _distances[x][y - 1] = distance;
                plan.push(pair<int, int>(x, y - 1));
            }
        }
        // Right
        if (y + 1 < this->_field_width) {
            distance = _distances[x][y] + _costs[_field[x][y + 1]];
            if (_used[x][y + 1] != -1 && _distances[x][y + 1] > distance) {
                _distances[x][y + 1] = distance;
                plan.push(pair<int, int>(x, y + 1));
            }
        }

        // Marking current
        _used[x][y] = true;
    }

    if (_distances[x1][y1] == MAX_INT) {
        *pathLength = -1;
        *path = "";
    } else {
        *pathLength = _distances[x1][y1];

        // Building reversed path
        string reversedPath;
        int distance = _distances[end.first][end.second]; // distance to end point
        while (end != start) {
            int x = end.first;
            int y = end.second;

            // Distance on previous step
            int prevDistance = distance - _costs[_field[x][y]];
            if (x - 1 >= 0 && _used[x - 1][y] != -1 && prevDistance == _distances[x - 1][y]) {
                end.first -= 1;
                reversedPath += 'S';
            } else if (x + 1 < this->_field_height && _used[x + 1][y] != -1 && prevDistance == _distances[x + 1][y]) {
                end.first += 1;
                reversedPath += 'N';
            } else if (y - 1 >= 0 && _used[x][y - 1] != -1 && prevDistance == _distances[x][y - 1]) {
                end.second -= 1;
                reversedPath += 'E';
            } else if (y + 1 < this->_field_width && _used[x][y + 1] != -1 && prevDistance == _distances[x][y + 1]) {
                end.second += 1;
                reversedPath += 'W';
            }
            distance = prevDistance;
        }

        // Reverse it back
        std::reverse(reversedPath.begin(), reversedPath.end());
        *path = reversedPath;
    }
}

int main () {
    // Field size
    int n, m;
    cin >> n >> m;

    // Start position
    int start_x, start_y;
    cin >> start_x >> start_y;
    start_x--;
    start_y--;
    pair<int, int> start(start_x, start_y);

    // Target position
    int end_x, end_y;
    cin >> end_x >> end_y;
    end_x--;
    end_y--;
    pair<int, int> end(end_x, end_y);

    // Field
    vector <vector <char>> field(n, vector<char>(m, '.'));
    char fieldElement;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> field[i][j];
        }
    }

    // Getting path and path length
    int* pathLength = new int;
    auto* path = new string;
    CivilizationField civilizationField(field);
    civilizationField.findPlayerWay(start, end, pathLength, path);

    // Printing output
    if (*pathLength == -1) {
        cout << -1 << "\n";
    } else {
        cout << *pathLength << "\n";
        for (char move: *path) {
            cout << move;
        }
        cout << "\n";
    }
    return 0;
}
