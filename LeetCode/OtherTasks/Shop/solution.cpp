#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int main() {
    int n, k;
    long long sum = 0;
    cin >> n >> k;
    vector <int> prices(n);
    for (int& price: prices) {
        cin >> price;
        sum += price;
    }
    std::sort(prices.begin(), prices.end(), std::greater<int>());
    for (size_t i = k - 1; i < prices.size(); i += k) {
        sum -= prices[i];
    }
    cout << sum << "\n";
    return 0;
}
