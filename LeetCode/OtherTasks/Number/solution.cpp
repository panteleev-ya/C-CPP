#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

bool numberPartsComparator(string np1, string np2) {
    return np1 + np2 > np2 + np1;
}

int main() {
    vector <string> v;
    string numberPart;
    while (cin >> numberPart ) {
        v.push_back(numberPart);
    }
    std::sort(v.begin(), v.end(), numberPartsComparator);
    for (auto np: v) {
        cout << np;
    }
    cout << "\n";
    return 0;
}
