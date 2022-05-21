#include <iostream>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class BreakPiggies {
public:
    explicit BreakPiggies(vector<vector<int>> graph) {
        this->_graph = std::move(graph);
        this->_used = vector<bool>(this->_graph.size(), false);
    }
    int breakMinimum() {
        int counter = 0;
        int n = (int) this->_graph.size();
        this->_cycles = vector<int>(n, -1);
        for (int i = 0; i < n; i++) {
            if (this->_cycles[i] == -1) {
                if (findCycles(i, i)) {
                    counter++;
                }
            }
        }
        return counter;
    }
private:
    vector<vector<int>> _graph;
    vector<bool> _used;
    vector<int> _cycles;

    bool findCycles(int start, int from) {
        _cycles[from] = start;
        for (int to: _graph[from]) {
            if (_cycles[to] != -1) {
                // means _cycles[to] == start => we ended in the start => cycle found
                if (_cycles[to] == start) {
                    return true;
                }
                return false;
            } else {
                return findCycles(start, to);
            }
        }
        return false;
    }
};

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>());
    int v;
    for (int i = 0; i < n; i++) {
        cin >> v;
        // graph[v - 1].push_back(i);
        graph[i].push_back(v - 1);
    }
    BreakPiggies breakPiggies(graph);
    cout << breakPiggies.breakMinimum() << "\n";
    return 0;
}
