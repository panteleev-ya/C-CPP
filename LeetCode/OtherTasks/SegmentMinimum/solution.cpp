#include <iostream>
#include <vector>
#include <deque>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::deque;

int main() {
    int n, bufferSize;
    cin >> n >> bufferSize;

    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // В двустороннюю очередь будем пихать индексы из nums
    deque<int> d;
    int localMin[n - bufferSize + 1];
    int ind = 0;

    // Заполняем двустороннюю очередь стартовыми значениями
    for (int i = 0; i < bufferSize - 1; i++) {
        // Удаляем те индексы, значения по которым не смогут стать минимумами
        while (!d.empty() && nums[d[d.size() - 1]] >= nums[i]) {
            d.pop_back();
        }

        d.push_back(i);
    }

    // Продолжаем заполнять и освобождать двустороннюю очередь
    for (int i = bufferSize - 1; i < n; i++) {
        // Удаляем слишком старые индексы
        if (!d.empty() && (d[0] <= i - bufferSize)) {
            d.pop_front();
        }
        // Удаляем те индексы, значения по которым не смогут стать минимумами
        while (!d.empty() && nums[d[d.size() - 1]] >= nums[i]) {
            d.pop_back();
        }

        d.push_back(i);

        localMin[ind] = nums[d[0]];
        ind++;
    }

    for (int i = 0; i < n - bufferSize + 1; i++) {
        cout << localMin[i] << " ";
    }
    cout << "\n";
    return 0;
}
