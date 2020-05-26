#include "Cube.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <deque>
using std::vector;
using std::string;
using std::cout;

// Представление кубика рубика
//       0 0 0
//       0 0(0) --> _state[0][1][2]
//       0 0 0
// 1 1 1 2 2 2 3 3 3 4 4 4
// 1 1 1 2 2 2 3 3 3 4 4 4
// 1 1 1 2 2 2 3 3 3 4 4 4
//       5 5 5
//       5 5 5
//       5 5 5
//
//
//        4 4 4
//      1 0 0 0 3
//      1 0 0 0 3
//      1 0 0 0 3
//        2 2 2

// Зависимости (лево, верх, право, низ):
// 0 -> 1 4 3 2
// 1 -> 4 0 2 5
// 2 -> 1 0 3 5
// 3 -> 2 0 4 5
// 4 -> 3 0 1 5
// 5 -> 1 2 3 4

// F == белый     == 2
// R == оранжевый == 3
// L == красный   == 1
// U == зеленый   == 0
// D == синий     == 5
// B == желтый    == 4

// Конструкторы
Cube::Cube(const char* input_file_path) {

    // _state[грань][линия][позиция в линии] = color;
    _state.assign(6, vector <vector <int>>(3, vector <int>(3, -1)));
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                _state[i][j][k] = i;
    /*
    for (size_t i = 0; i < 6; i++)
        for (size_t j = 0; j < 3; j++) {
            input >> _state[i][j][0];
            input >> _state[i][j][1];
            input >> _state[i][j][2];
        }
    */

    // Связи между гранями (какие из них соседние)
    _connected = { { 1, 4, 3, 2 },
                   { 4, 0, 2, 5 },
                   { 1, 0, 3, 5 },
                   { 2, 0, 4, 5 },
                   { 3, 0, 1, 5 },
                   { 1, 2, 3, 4 } };

    // Связи между номерами граней и типами операции
    _margin = { {'U', 0}, {'L', 1}, {'F', 2}, {'R', 3}, {'B', 4}, {'D', 5} };

    // Индексы "соседей" у любой грани
    _neigh = { { { {0, 2}, {0, 1}, {0, 0} }, { {0, 2}, {0, 1}, {0, 0} }, { {0, 2}, {0, 1}, {0, 0} }, { {0, 2}, {0, 1}, {0, 0} } },
			   { { {2, 2}, {1, 2}, {0, 2} }, { {0, 0}, {1, 0}, {2, 0} }, { {0, 0}, {1, 0}, {2, 0} }, { {0, 0}, {1, 0}, {2, 0} } },
			   { { {2, 2}, {1, 2}, {0, 2} }, { {2, 0}, {2, 1}, {2, 2} }, { {0, 0}, {1, 0}, {2, 0} }, { {0, 2}, {0, 1}, {0, 0} } },
			   { { {2, 2}, {1, 2}, {0, 2} }, { {2, 2}, {1, 2}, {0, 2} }, { {0, 0}, {1, 0}, {2, 0} }, { {2, 2}, {1, 2}, {0, 2} } },
			   { { {2, 2}, {1, 2}, {0, 2} }, { {0, 2}, {0, 1}, {0, 0} }, { {0, 0}, {1, 0}, {2, 0} }, { {2, 0}, {2, 1}, {2, 2} } },
			   { { {2, 0}, {2, 1}, {2, 2} }, { {2, 0}, {2, 1}, {2, 2} }, { {2, 0}, {2, 1}, {2, 2} }, { {2, 0}, {2, 1}, {2, 2} } }
    };

	// Соседние цвета каждого ребра
    _two_con = { { {0, 1}, {0, 1}, {0, 1}, {0, 1} },
				 { {1, 2}, {1, 0}, {1, 0}, {1, 0} },
			     { {1, 2}, {2, 1}, {1, 0}, {0, 1} },
				 { {1, 2}, {1, 2}, {1, 0}, {1, 2} },
				 { {1, 2}, {0, 1}, {1, 0}, {2, 1} },
				 { {2, 1}, {2, 1}, {2, 1}, {2, 1} }
    };

    // Соседние цвета каждого угла
	_three_con = { { {0, 0, 0, 2}, {0, 0, 0, 2}, {0, 0, 0, 2}, {0, 0, 0, 2} },
                   { {0, 2, 0, 0}, {2, 0, 0, 0}, {2, 0, 0, 0}, {2, 0, 2, 2} },
                   { {0, 2, 2, 0}, {2, 2, 0, 0}, {2, 0, 0, 2}, {0, 0, 2, 2} },
                   { {0, 2, 2, 2}, {0, 2, 0, 0}, {2, 0, 2, 2}, {0, 2, 2, 2} },
                   { {0, 2, 0, 2}, {0, 0, 0, 0}, {2, 0, 2, 0}, {2, 2, 2, 2} },
                   { {2, 2, 2, 0}, {2, 2, 2, 0}, {2, 2, 2, 0}, {2, 2, 2, 0} },
	};

	// Координаты ребер на грани
    _edges = { {1, 0}, {0, 1}, {1, 2}, {2, 1} };

	// Координаты углов на грани
    _corners = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };

    std::ifstream input(input_file_path);
    int rotates;
    input >> rotates;
    for (std::string r; std::getline(input, r); ) {
        char buffer;
        for (char i : r) {
            buffer = i;
        }
        if (r != "")
            rotate(r);
    }
    input.close();
}
Cube::Cube() {
	// Все объяснено в конструкторе выше
    _state.assign(6, vector <vector <int>>(3, vector <int>(3, -1)));
    _connected = { { 1, 4, 3, 2 }, { 4, 0, 2, 5 }, { 1, 0, 3, 5 }, { 2, 0, 4, 5 }, { 3, 0, 1, 5 }, { 1, 2, 3, 4 } };
    _margin = { {'U', 0}, {'L', 1}, {'F', 2}, {'R', 3}, {'B', 4}, {'D', 5} };
    _neigh = { { { {0, 2}, {0, 1}, {0, 0} }, { {0, 2}, {0, 1}, {0, 0} }, { {0, 2}, {0, 1}, {0, 0} }, { {0, 2}, {0, 1}, {0, 0} } },
               { { {2, 2}, {1, 2}, {0, 2} }, { {0, 0}, {1, 0}, {2, 0} }, { {0, 0}, {1, 0}, {2, 0} }, { {0, 0}, {1, 0}, {2, 0} } },
               { { {2, 2}, {1, 2}, {0, 2} }, { {2, 0}, {2, 1}, {2, 2} }, { {0, 0}, {1, 0}, {2, 0} }, { {0, 2}, {0, 1}, {0, 0} } },
               { { {2, 2}, {1, 2}, {0, 2} }, { {2, 2}, {1, 2}, {0, 2} }, { {0, 0}, {1, 0}, {2, 0} }, { {2, 2}, {1, 2}, {0, 2} } },
               { { {2, 2}, {1, 2}, {0, 2} }, { {0, 2}, {0, 1}, {0, 0} }, { {0, 0}, {1, 0}, {2, 0} }, { {2, 0}, {2, 1}, {2, 2} } },
               { { {2, 0}, {2, 1}, {2, 2} }, { {2, 0}, {2, 1}, {2, 2} }, { {2, 0}, {2, 1}, {2, 2} }, { {2, 0}, {2, 1}, {2, 2} } }
    };
    _two_con = { { {0, 1}, {0, 1}, {0, 1}, {0, 1} },
                 { {1, 2}, {1, 0}, {1, 0}, {1, 0} },
                 { {1, 2}, {2, 1}, {1, 0}, {0, 1} },
                 { {1, 2}, {1, 2}, {1, 0}, {1, 2} },
                 { {1, 2}, {0, 1}, {1, 0}, {2, 1} },
                 { {2, 1}, {2, 1}, {2, 1}, {2, 1} }
    };
    _three_con = { { {0, 0, 0, 2}, {0, 0, 0, 2}, {0, 0, 0, 2}, {0, 0, 0, 2} },
                   { {0, 2, 0, 0}, {2, 0, 0, 0}, {2, 0, 0, 0}, {2, 0, 2, 2} },
                   { {0, 2, 2, 0}, {2, 2, 0, 0}, {2, 0, 0, 2}, {0, 0, 2, 2} },
                   { {0, 2, 2, 2}, {0, 2, 0, 0}, {2, 0, 2, 2}, {0, 2, 2, 2} },
                   { {0, 2, 0, 2}, {0, 0, 0, 0}, {2, 0, 2, 0}, {2, 2, 2, 2} },
                   { {2, 2, 2, 0}, {2, 2, 2, 0}, {2, 2, 2, 0}, {2, 2, 2, 0} },
    };
    _edges = { {1, 0}, {0, 1}, {1, 2}, {2, 1} };
    _corners = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
}


// Методы
bool Cube::check_state() { // проверяет, может ли быть такая комбинация цветов на кубике
    vector <int> counters(6, 0); // количество встретившихся цветов
    for (const auto& margin: _state)
        for (const auto& line: margin)
            for (const auto& color: line)
                counters[color % 6]++;
    for (const auto& c: counters) {
        if (c != 9)
            return false;
    }
    return true;
}

void Cube::rotate(int type, int dir) {
    vector <string> options = { "U",   "L",   "F",   "R",   "B",   "D",
    							"U\'", "L\'", "F\'", "R\'", "B\'", "D\'" };
    _rotate(options[(type % 6) + 6 * (dir % 2)]);
}
void Cube::rotate(string type) {
    const bool is_correct = parse_rotate_arg(type);
    if (!is_correct) {
        cout << "This type of operation does not exist!\nUse one of this(m.b. reversed): R, L, U, D, F, B\n";
        return;
    }
    _rotate(type);
}
void Cube::_rotate(string type) {
	const bool reversed = type.length() > 1; // reversed = true, если движение против часовой стрелки
	int start = reversed ? 3 : 0;
	int step = reversed ? -1 : 1;
	int last = reversed ? 0 : 3;
    const int margin = _margin[type[0]]; // выбираем грань
    vector <int> buff(3);
    vector <vector <vector <int>>> cur_neigh = _neigh[_margin[type[0]]]; // выбираем "матрицу перехода" цветов
    // Принцип работы: двигаем внешний круг, потом двигаем внутренний круг
    // 
    // Что пихать в буффер на внешнем круге?
    //   input -> _margin -> _connected ->   _state
    //     F   ->    2    ->   1 0 3 5  -> c1 c0 c3 c5
    //
    // Что пихать в буффер на внутреннем круге?
    //   1) Запихиваем все, что вокруг центра в дек
    //   2) Берем с конца -> кидаем в начало (х2)
    //   3) Все по "очереди" возвращаем на места
    
    // Крутим внешний круг
    buff = { _state[ _connected[margin][(last + 1) % 4] ][ cur_neigh[(last + 1) % 4][0][0] ][ cur_neigh[(last + 1) % 4][0][1] ],
             _state[ _connected[margin][(last + 1) % 4] ][ cur_neigh[(last + 1) % 4][1][0] ][ cur_neigh[(last + 1) % 4][1][1] ],
             _state[ _connected[margin][(last + 1) % 4] ][ cur_neigh[(last + 1) % 4][2][0] ][ cur_neigh[(last + 1) % 4][2][1] ] };
    for (size_t i = start; i != last + step; i += step)
        for (size_t j = 0; j < 3; j++)
            std::swap(buff[j], _state[_connected[margin][(i + 1) % 4]][cur_neigh[(i + 1) % 4][j][0]][cur_neigh[(i + 1) % 4][j][1]]);
	// Крутим внутренний круг
    start = reversed ? 8 : 0;
    step = reversed ? -1 : 1;
    last = reversed ? 0 : 8;
    vector <vector <int>> cells = { {0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0} };
    int color_buffer = _state[margin][cells[7][0]][cells[7][1]];
	for (size_t j = 0; j < 2; j++)
	    for (size_t i = start; i != last + step; i += step)
	        std::swap(color_buffer, _state[margin][ cells[i % 8][0] ][ cells[i % 8][1] ]);
}
void Cube::print_margin(int x) {
	for (const auto& i: _state[x]) {
        for (auto j : i)
            cout << j << ' ';
        cout << "\n";
	}
}
vector<vector<int>> Cube::get_margin(int x) {
    return _state[x % 6];
}
int Cube::get_neigh_color(int margin, int type, int pos, int dir) { // type == 2 means _two_con, type == 3 means _three_con
	const int neigh = (type == 2) ? _connected[margin][pos % 4] : _connected[margin][(pos + (dir % 2)) % 4];
    const int x = (type == 2) ? _two_con[margin % 6][pos][0] : _three_con[margin % 6][pos % 4][0 + 2 * (dir % 2)];
    const int y = (type == 2) ? _two_con[margin % 6][pos][1] : _three_con[margin % 6][pos % 4][1 + 2 * (dir % 2)];
    return _state[neigh][x][y];
}

void Cube::pif_paf(int margin, int corner_ind, int type) {
    if (type == 1) { // правый пиф-паф
        vector <int> conn = _connected[margin];
        this->rotate(conn[corner_ind], 1);
        this->rotate(conn[(corner_ind + 1) % 4], 0);
        this->rotate(conn[corner_ind], 0);
        this->rotate(conn[(corner_ind + 1) % 4], 1);
    }
}

// Операторы
/*std::istream& operator>>(std::istream& input, Cube& obj) {
    for (size_t i = 0; i < 6; i++)
        for (size_t j = 0; j < 3; j++) {
            input >> obj._state[i][j][0];
            input >> obj._state[i][j][1];
            input >> obj._state[i][j][2];
        }
    return input;
}*/
std::istream& operator>>(std::istream& input, Cube& obj) {
    cout << "Input number of rotates: ";
    int rotates;
    input >> rotates;
    cout << "Input " << rotates << " rotates: ";
	for (size_t i = 0; i < rotates; i++) {
        string r;
        input >> r;
        obj.rotate(r);
	}
    return input;
}
std::ostream& operator<<(std::ostream& output, const Cube& obj) {
    // output << "Current state is:\n";
    for (size_t j = 0; j < 3; j++) // выводит 1-ую грань
        output << "       " << obj._state[0][j][0] << ' ' << obj._state[0][j][1] << ' ' << obj._state[0][j][2] << "\n";
    for (size_t j = 0; j < 3; j++) {// выводит 2-5 грани
        for (size_t i = 1; i < 5; i++)
            output << ' ' << obj._state[i][j][0] << ' ' << obj._state[i][j][1] << ' ' << obj._state[i][j][2];
        output << "\n";
    }
    for (size_t j = 0; j < 3; j++) // выводит 6-ую грань
        output << "       " << obj._state[5][j][0] << ' ' << obj._state[5][j][1] << ' ' << obj._state[5][j][2] << "\n";
    return output;
}
Cube& Cube::operator=(const Cube& other_cube) = default;

// Вспомогательные функции
bool Cube::parse_rotate_arg(string& s) { // преобразует входные данные в правильную операцию
    std::map <char, char> directions = {{'r', 'R'}, {'R', 'R'},
    								    {'l', 'L'}, {'L', 'L'},
                                        {'u', 'U'}, {'U', 'U'},
                                        {'d', 'D'}, {'D', 'D'},
                                        {'f', 'F'}, {'F', 'F'},
                                        {'b', 'B'}, {'B', 'B'}};
    const auto is_exist = directions.find(s[0]);
	if (is_exist == directions.end()) {
        return false;
	}
    string new_s;
	new_s += is_exist->second;
	if (s.length() > 1)
        new_s += "\'";
    s = new_s;
    cout << new_s << "\n";
    return true;
}