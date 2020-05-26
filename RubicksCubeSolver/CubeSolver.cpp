#include "CubeSolver.h"
#include <iostream>
#include <ctime>
using std::cout;

// Получение суммы элементов вектора
template <class T>
T sum(const vector <T>& v) {
	T s = 0;
	for (auto i : v)
		s = s + i;
	return s;
}



CubeSolver::CubeSolver(Cube cube) {
	std::srand(unsigned(std::time(0)));
	_cube = cube;
}

// Алгоритм сборки
void CubeSolver::make_white_cross() {
	vector <int> margins = { 0, 1, 3, 4, 5 };
	const vector <std::pair<int, int>> first_option = { {1, 1}, {1, 3}, {0, 0}, {0, 2}, {3, 1}, {3, 3}, {5, 0}, {5, 2} };
	const vector <std::pair<int, int>> second_option = { {1, 0}, {0, 1}, {3, 2}, {5, 3} };
	const vector <std::pair<int, int>> third_option = { {1, 2}, {0, 3}, {3, 0}, {5, 1} };
	// Собираем обычный блять крест на белой грани
	while (!check_white_cross()) { // пока крест не собрался
		for (auto mar_ind : margins) { // проверяем все грани на наличие белых ребер
			auto m = _cube.get_margin(mar_ind); // берем i-ую грань
			for (int edge_ind = 0; edge_ind < 4; edge_ind++) { // проверяет все 4 ребра на данной грани, edge_ind - номер ребра на i-ой грани
				vector <int> edge = _cube._edges[edge_ind]; // edge_ind-ое ребро данной грани
				if (m[edge[0]][edge[1]] == 2) { // если это ребро белого цвета
					if (mar_ind == 4) { // если грань желтая
						free_the_place(2, edge_ind); // освобождаем белому ребро место
						const int target = _cube._connected[2][edge_ind]; // грань, которую надо повернуть, чтобы поставить наше белое ребро на место
						_cube.rotate(target, 0); // ставим наше белое ребро на белую грань
						_cube.rotate(target, 0);
					}
					else {
						const std::pair <int, int> mar_and_edge = {mar_ind, edge_ind};
						check_mar_edge(mar_and_edge, first_option, second_option, third_option);
					}
				}
			}
		}
	}
}

void CubeSolver::correct_white_cross() {
	// Пока 2 или 4 ребра не совпадут с гранями, поворачиваем верхнюю грань
	// Если совпали 4 - все супер
	// Если совпали 2:
	//		Если они соседи ((current_cross_state[1] - current_cross_state[0]) % 2 == 1), применяем формулу для соседей относительно первого
	//		Если они не соседи, применяем другую формулу относительно первого
	vector <int> current_cross_state = check_cross_state();
	int rotate_counter = 0; // вдруг я ошибся, и не всегда 2 или 4 ребра будут совпадать
	while (current_cross_state.size() < 2 && rotate_counter < 5) {
		_cube.rotate(2, 0); // поворачиваем верхнюю грань
		current_cross_state = check_cross_state(); // обновляем информацию о гранях
		rotate_counter++;
	}
	if (rotate_counter >= 5) {
		cout << "This state broke my algorithm and my hopes...\n";
		return;
	}
	if (current_cross_state.size() == 2) { // в случае с 4-мя готовыми делать ничего не нужно
		if ((current_cross_state[1] - current_cross_state[0]) % 2 == 1) { // это соседи
			cout << _cube;
			// Опускаем оба ребра на желтую грань
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[1], 0);
			_cube.rotate(current_cross_state[1], 0);
			// Ставим один из них на его место
			_cube.rotate(4, 0);
			// Возвращаем его на белую грань
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[0], 0);
			// Ставим второй на его место
			_cube.rotate(4, 1);
			_cube.rotate(4, 1);
			// Ставим его на его место
			_cube.rotate(current_cross_state[1], 0);
			_cube.rotate(current_cross_state[1], 0);
		}
		else {
			// Опускаем оба ребра на желтую грань
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[1], 0);
			_cube.rotate(current_cross_state[1], 0);
			// Меняем их местами (поворачиваем желтую грань 2 раза)
			_cube.rotate(4, 0);
			_cube.rotate(4, 0);
			// Возвращаем их на белую грань
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[0], 0);
			_cube.rotate(current_cross_state[1], 0);
			_cube.rotate(current_cross_state[1], 0);
		}
	}
}
void CubeSolver::first_layer() {
	vector <int> corner_state = find_white_corner();
	int m = corner_state[0];
	int ind = corner_state[1];
	while (m != -1) { // пока еще есть белые углы не на белой грани
		vector <int> conn = _cube._connected[m]; // грани, смежные с данной
		if (m == 4) { // если это желтая грань
			// vector <int> neigh_colors = _cube._three_con[4][ind]; // координаты соседних цветов нашего угла
			// Пока (справа от угла не будет его нижний цвет и снизу от угла не будет его правый цвет)
			// Поворачиваем желтую грань
			// Справа - conn[ind], нижний - _cube.get_neigh_color(4, 3, ind, 1)
			// Снизу - conn[(ind + 1) % 4], правый - _cube.get_neigh_color(4, 3, ind, 0)
			set_corner(m, ind); // работает для углов, стоящих на желтой грани над своим местом
		}
		else {
			vector <vector <int>> down_corners = {
				{3, 2}, {2, 1}, {0, 3}, {1, 0}
			};
			vector <vector <int>> up_corners = {
				{0, 1}, {3, 0}, {1, 2}, {2, 3}
			};
			int type;
			if (ind == down_corners[m / 2 + m % 2][0]) { // левый нижний
				type = 0;
			}
			else if (ind == down_corners[m / 2 + m % 2][1]) { // правый нижний
				type = 1;
			}
			else if (ind == up_corners[m / 2 + m % 2][0]) {  // левый верхний
				type = 2;
			}
			else {  // правый верхний
				type = 3;
			}
			get_corner_up(m, ind, type);
			// set_corner(m, ind);
		}
		corner_state = find_white_corner();
		m = corner_state[0];
		ind = corner_state[1];
	}
}

// Методы
void CubeSolver::generate_random_state(Cube& obj) {
	const int count = rand() % 11 + 10; // количество поворотов граней
	// Все варианты поворотов
	vector <const char*> margins = { "U", "L", "F", "R", "B", "D", "U\'", "L\'", "F\'", "R\'", "B\'", "D\'" };
	for (size_t i = 0; i < count; i++)
		obj.rotate(margins[rand() % 12]);
}
void CubeSolver::synch(Cube& cube) {
	cube = _cube;
}

void CubeSolver::r_synch(Cube& cube) {
	_cube = cube;
}

// Вспомогательные функции
void CubeSolver::reverse_edge(int margin, int edge_ind) {
	const int target_ind = (edge_ind + 2) % 4;
	const int not_connected = 15 - sum(_cube._connected[margin]) - margin; // находим такую грань, которая не граничит с данной
	const int target1 = _cube._connected[margin][target_ind];
	const int target2 = _cube._connected[margin][(target_ind + 1) % 4];
	_cube.rotate(target1, 1); // прячем наше ребро вниз
	_cube.rotate(target2, 0); // убираем наше ребро на желтый слой
	_cube.rotate(not_connected, 0); // двигаем наше ребро ПОД его "законное" место
	_cube.rotate(target2, 1); // возвращаем левую грань на исходное место
	_cube.rotate(target1, 0);
	_cube.rotate(target1, 0); // двигаем наше ребро НА его "законное место"
}

bool CubeSolver::check_white_cross() {
	const int color = 2; // цвет белой грани
	auto white = _cube.get_margin(color); // получает состояние белой грани
	for (auto edge: _cube._edges) // чекает все ребра на белой грани
		if (white[edge[0]][edge[1]] != color) // если хоть одно из ребер не белое, возвращает false
			return false;
	return true;
}
void CubeSolver::free_the_place(int margin, int ind) {
	for (int j = 0; j < 3; j++) { // повторяем операцию не больше трех раз
		vector <int> e = check_edge(margin, ind);
		if (e[0] != 2 && e[1] != 2) // если свободное место нашлось, заканчиваем
			break;
		_cube.rotate(margin, 0); // поворачиваем белую грань, пытаясь найти свободное место (мы его точно найдем)
	}
}
void CubeSolver::fill_the_place(int margin, int ind) {
	const int target = _cube._connected[margin][ind]; // выбираем грань, которую нужно повернуть, чтобы заполнить ind-ое ребро
	for (int j = 0; j < 3; j++) { // повторяем операцию не больше трех раз
		_cube.rotate(target, 0); // поворачиваем target грань, пытаясь заполнить свободное место (мы его точно заполним)
		vector <int> e = check_edge(margin, ind);
		if (e[0] == margin || e[1] == margin) // если наше ребро встало на место, заканчиваем
			break;
	}
}
vector <int> CubeSolver::check_edge(int margin, int ind) {
	vector <int> e(2); // вернет цвета данного ребра на данной грани и на смежной
	e[0] = _cube._state[margin][_cube._edges[ind][0]][_cube._edges[ind][1]]; // цвет данного ребра на данной грани
	const int neigh_margin = _cube._connected[margin][ind]; // смежная грань, на которой также лежит данное ребро
	vector <int> neigh_ind = _cube._two_con[margin][ind]; // индекс данного ребра на смежной грани
	e[1] = _cube._state[neigh_margin][neigh_ind[0]][neigh_ind[1]]; // цвет данного ребра на смежной грани
	return e;
}
void CubeSolver::check_mar_edge(std::pair<int, int> mep, vector<std::pair<int, int>> fo, vector<std::pair<int, int>> so, vector<std::pair<int, int>> to) {
	for (auto p : fo) {
		if (p == mep) {
			free_the_place(2, mep.second); // освобождаем белому ребру место
			fill_the_place(2, mep.second); // ставим его на освобожденное место
			return;
		}
	}
	for (auto p : so) {
		if (p == mep) {
			free_the_place(2, mep.second); // освобождаем белому ребру место
			_cube.rotate(mep.first, 0);
			_cube.rotate(mep.first, 0); // ставим его на освобожденное место
			return;
		}
	}
	for (auto p : to) {
		if (p == mep) {
			reverse_edge(2, mep.second);
			return;
		}
	}
}
vector<int> CubeSolver::check_cross_state() {
	// Проверяем все смежные с белой грани (лево, верх, право, низ) == _cube._connecetd[2][i]
	// Смотрим, чтобы на i-ой смежной грани (i+2)%4-ое ребро было цвета i
	// Если да - добавляем i в вектор correct, если нет, идем смотреть дальше
	vector <int> correct; // будет содержать номера граней, на которых белое ребро совпадает по цвету с центром грани
	vector <vector <int>> e = _cube._edges; // вектор координат ребер на грани (любой)
	for (int conn_ind = 0; conn_ind < 4; conn_ind++) { // проверяем все грани, смежные с белой гранью (лево, верх, право, низ)
		int margin_ind = _cube._connected[2][conn_ind];
		if (_cube._state[margin_ind][e[(conn_ind + 2) % 4][0]][e[(conn_ind + 2) % 4][1]] == margin_ind) { // если белое ребро на этой грани такого же цвета как и центр грани
			correct.push_back(conn_ind);
		}
	}
	return correct;
}
vector<int> CubeSolver::find_white_corner() {
	vector <int> corner_info(3); // { margin, x, y }
	vector <int> margins = { 4, 0, 1, 3, 5 };
	for (auto m : margins) // смотрим на каждую грань из списка по очереди
		for (int i = 0; i < 4; i++) { // смотрим на каждый угол на этой грани
			auto e = _cube._corners[i];
			if (_cube._state[m][e[0]][e[1]] == 2) // если этот угол белый
				return { m, i }; // возвращаем сторону, на которой мы его нашли и его номер
		}
	return { -1, -1 };
}

void CubeSolver::set_corner(int margin, int ind) {
	while (_cube._connected[margin][ind] != _cube.get_neigh_color(margin, 3, ind, 1) && _cube._connected[margin][(ind + 1) % 4] != _cube.get_neigh_color(margin, 3, ind, 0)) {
		_cube.rotate(4, 0);
		ind = (ind + 1) % 4; // из-за поворота этой грани индекс угла меняется
	}
	_cube.rotate(_cube._connected[margin][(ind + 1) % 4], 1); // переворачиваем угол
	_cube.rotate(margin, 0); // прячем его, чтобы вернуть на место то, что перевернулось вместе с углом
	_cube.rotate(_cube._connected[margin][(ind + 1) % 4], 0); // возвращаем грань на прежднее место
	_cube.rotate(margin, 0); // готовим угол к пиф-пафу
	_cube.rotate(margin, 0);
	_cube.pif_paf(margin, ind, 1); // пиф-пафом ставим его на место
}

void CubeSolver::get_corner_up(int margin, int ind, int type) {
	if (type == 0) { // левый нижний
		_cube.rotate(_cube._connected[margin][(ind + 1) % 4], 1);
		_cube.rotate(4, 1);
		_cube.rotate(_cube._connected[margin][(ind + 1) % 4], 0);
	}
	else if (type == 1) { // правый нижний
		_cube.rotate(_cube._connected[margin][ind], 0);
		_cube.rotate(4, 0);
		_cube.rotate(_cube._connected[margin][ind], 1);
	}
	else if (type == 2) { // левый верхний
		vector <int> circle_margins = { 0, 1, 5, 3 };
		vector <int> circle_inds = { 0, 3, 2, 1 };
		int m_ind = 0;
		for (int i = 0; i < circle_margins.size(); i++) {
			if (circle_margins[i] == margin) {
				m_ind = i;
				break;
			}
		}
		int i_ind = 0;
		for (int i = 0; i < circle_inds.size(); i++) {
			if (circle_inds[i] == ind) {
				i_ind = i;
				break;
			}
		}
		while (_cube.get_neigh_color(margin, 3, ind, 0) != _cube._connected[margin][ind]) {
			_cube.rotate(4, 0);
			margin = circle_margins[(m_ind + 1) % 4];
			ind = circle_inds[(i_ind + 1) % 4];
		}
		_cube.rotate(_cube._connected[margin][ind], 1);
		_cube.rotate(4, 0);
		_cube.rotate(_cube._connected[margin][ind], 0);
	}
	else if (type == 3) { // правый верхний
		cout << _cube;
		vector <int> circle_margins = { 0, 1, 5, 3 };
		vector <int> circle_inds = { 0, 3, 2, 1 };
		int m_ind = 0;
		for (int i = 0; i < circle_margins.size(); i++) {
			if (circle_margins[i] == margin) {
				m_ind = i;
				break;
			}
		}
		int i_ind = 0;
		for (int i = 0; i < circle_inds.size(); i++) {
			if (circle_inds[i] == ind) {
				i_ind = i;
				break;
			}
		}
		while (_cube.get_neigh_color(margin, 3, ind, 1) != _cube._connected[margin][(ind + 1) % 4]) {
			_cube.rotate(4, 0);
			margin = circle_margins[(m_ind + 1) % 4];
			ind = circle_inds[(i_ind + 1) % 4];
		}
		_cube.rotate(_cube._connected[margin][(ind + 1) % 4], 0);
		_cube.rotate(4, 1);
		_cube.rotate(_cube._connected[margin][(ind + 1) % 4], 1);
	}
}

