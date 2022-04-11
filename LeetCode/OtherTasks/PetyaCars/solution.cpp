#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::map;
using std::queue;
using std::priority_queue;

auto gucciGang = []() {std::ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);return 0;}();
int main() {
    // Машинки на полке, на полу и количество запросов Пети
    int carsCount, floorSize, requestsCount;
    cin >> carsCount >> floorSize >> requestsCount;

    // Храним запросы
    int requests[requestsCount];

    // Храним информацию о наличии машинки на полу
    vector<bool> onFloor(carsCount);

    // Храним списки индексов использований машинок
    vector<queue<int>> carsUsagesIndexes(carsCount);

    // Приоритетная очередь машинок на убирание с пола
    priority_queue<int, vector<int>, std::less<>> pq;

    // Считаем действия мамы Пети
    int movesCounter = 0;

    // Вводим данные
    int car;
    for (int i = 0; i < requestsCount; i++) {
        cin >> car;

        requests[i] = car;

        onFloor[car - 1] = false;

        carsUsagesIndexes[car - 1].push(i);
    }

    // Обрабатываем запросы
    int carToRemove;
    for (int i = 0; i < requestsCount; i++) {
        car = requests[i] - 1;

        // Если этой машинки нет на полу
        if (!onFloor[car]) {
            // Инкриминируем действия мамы Пети
            movesCounter++;

            // Если ее нельзя просто так положить на пол
            if (floorSize <= 0) {
                // Убираем одну машинку с пола
                carToRemove = pq.top();
                if (carToRemove >= 500001) {
                    onFloor[carToRemove - 500001] = false;
                } else {
                    onFloor[requests[carToRemove] - 1] = false;
                }
                pq.pop();
            }

            onFloor[car] = true;
            floorSize--;
        }
        // Обновляем информацию о встречаемости машинки
        carsUsagesIndexes[car].pop();

        // Кладем машинку на пол
        if (carsUsagesIndexes[car].empty()) {
            // Никогда не будет использоваться
            pq.push(500001 + car);
        } else {
            pq.push(carsUsagesIndexes[car].front());
        }
    }

    cout << movesCounter << "\n";
    return 0;
}
