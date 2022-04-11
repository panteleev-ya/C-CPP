#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::string;

const size_t alphabetSize = 26;
const string alphabet = "abcdefghijklmnopqrstuvwxyz";
int weights[alphabetSize];

bool compareSymbolsByWeight(size_t s1, size_t s2) {
    // Сортируем в обратном порядке
    // Если вес s1 меньше либо равен весу s2
    if (weights[s1] <= weights[s2]) {
        // s1 левее s2
        return true;
    } else {
        // Иначе s1 правее s2
        return false;
    }
}

int main() {
    string s;
    cin >> s;

    for (int& weight : weights) {
        cin >> weight;
    }

    string maxString;

    // Собираем в этот вектор все такие символы (а точнее их индексы в алфавите), количество которых больше либо равно 2
    // Чтобы взять два из них и разделить максимально возможным расстоянием для увеличения веса строки maxString
    vector <size_t> countableChars;

    // Флаги "взятости" символа
    vector <bool> isCounted(alphabetSize, false);

    // Количества символов, найденных в строке s
    vector <int> charsCount(alphabetSize, 0);

    // Проходимся по всем символам в s
    for (char symbol : s) {
        size_t symbolIndex = symbol - 'a';
        charsCount[symbolIndex]++;

        // Если количество некого символа стало 2, а мы еще не закинули его в "очередь" на добавление в начало и конец
        // "Закидываем" два таких символа в очередь, ставим флаг, что он закинут и уменьшаем их количество на 2
        if (!isCounted[symbolIndex] && charsCount[symbolIndex] >= 2) {
            isCounted[symbolIndex] = true;
            charsCount[symbolIndex] -= 2;
            countableChars.push_back(symbolIndex);
        }
    }

    // Сортируем "добавляемые" символы по весам, чтобы символы с большим весом были дальше друг от друга
    std::sort(countableChars.begin(), countableChars.end(), compareSymbolsByWeight);

    // Добавляем в строку те символы, расположение которых нам не важно (которые на вес не влияют)
    for (size_t i = 0; i < charsCount.size(); i++) {
        for (size_t j = 0; j < charsCount[i]; j++) {
            maxString += alphabet[i];
        }
    }

    // "Оборачиваем" строку слева и справа символами, которые влияют на ее вес оптимальным образом
    for (size_t index : countableChars) {
        char symbol = alphabet[index];
        maxString = symbol + maxString + symbol;
    }

    cout << maxString << "\n";
    return 0;
}
