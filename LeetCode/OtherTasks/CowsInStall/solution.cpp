#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> coordinates(n);
    for (size_t i = 0; i < n; i++) {
        cin >> coordinates[i];
    }
    int start = 0;
    int end = coordinates[n - 1] - coordinates[0] + 1;
    int mid, cowsCounter, lastCowCoordinate, coordinate;

    // Идем бинарным поиском по ответу
    while (start < end) {
        // Задаем условно-минимальное расстояние между двумя соседними коровами в mid
        mid = (start + end) / 2;
        cowsCounter = 1;
        lastCowCoordinate = coordinates[0];

        // Смотрим, сколько коров можно поместить с расстоянием не меньше чем mid друг от друга
        for (size_t i = 1; i < coordinates.size(); i++) {
            coordinate = coordinates[i];
            if (coordinate - lastCowCoordinate > mid) {
                cowsCounter += 1;
                lastCowCoordinate = coordinate;
            }
        }
        if (cowsCounter >= k) {
            // Если удалось уместить k коров - проверяем правую половину
            start = mid + 1;
        } else {
            // Иначе проверяем левую половину
            end = mid;
        }
    }
    cout << start << "\n";
    return 0;
}
