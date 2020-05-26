#pragma once
#ifndef LAB8_CUBE_H
#define LAB8_CUBE_H

#include <map>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Cube {
public:
	friend class CubeSolver;
	
	// Конструкторы
    explicit Cube(const char* path); // ввод состояния кубика из файла
	Cube();

	// Методы
    bool check_state(); // проверка правильности его состояния
	void rotate(string type);
	void rotate(int type, int dir);
	void print_margin(int x);
	vector <vector <int>> get_margin(int x);
	int get_neigh_color(int margin, int type, int pos, int dir);
	void pif_paf(int margin, int corner_ind, int type);

	// Операторы
    friend std::istream& operator>> (std::istream& in, Cube& obj); // оператор ввода объекта из консоли
    friend std::ostream& operator<< (std::ostream& out, const Cube& obj); // вывода объекта в консоль (состояния)
	Cube& operator=(const Cube& other_cube);
private:
	// _state[грань][линия][позиция в линии] = color;
	vector <vector <vector <int>>> _state; // хранит состояние кубика на данный момент
	vector <vector <int>> _connected;
	std::map <char, int> _margin;
	vector <vector <vector <vector <int>>>> _neigh;
	vector <vector <vector <int>>> _two_con;
	vector <vector <vector <int>>> _three_con;
	vector <vector <int>> _edges;
	vector <vector <int>> _corners;

	// Вспомогательные функции
	bool parse_rotate_arg(string& s);
	void _rotate(string type);
};

#endif //LAB8_CUBE_H
