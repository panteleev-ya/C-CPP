#include <iostream>
#include "Cube.h"
#include "CubeSolver.h"
using std::vector;
using std::cout;

// F == белый     == 2
// R == оранжевый == 3
// L == красный   == 1
// U == зеленый   == 0
// D == синий     == 5
// B == желтый    == 4

int main() {
	
    Cube cube("rubik.txt");
    cout << cube;
	
	vector <const char*> putaem = { "L", "D", "B", "F" };
	for (auto i : putaem) {
		cout << i << "\n";
		cube.rotate(i);
		cout << cube;
	}

	cout << "Making white cross:\n";
	CubeSolver algo(cube);
	algo.make_white_cross();
	algo.synch(cube);
	cout << cube;

	cout << "Making white cross correct\n";
	algo.correct_white_cross();
	algo.synch(cube);
	cout << cube;


	// Готовим куб к проверке на желтой грани
	/*cout << "Preparing cube a little bit\n";
	cube.rotate(5, 1);
	cube.rotate(4, 1);
	cube.rotate(5, 0);
	algo.r_synch(cube);
	cout << cube;*/
	
	cout << "Making first layer\n";
	algo.first_layer();
	algo.synch(cube);
	cout << cube;
    return 0;
}