#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <list>
#include "D3-Heap.h"

using namespace std;

vector<int> Keys = { 8, 6, 12, 2, 1, 4, 5, 10, 11, 3, 7, 9 };

D3_Heap Heap;


int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	Heap.create(Keys);
	Heap.Output();
	Heap.delete_min();
	Heap.Output();
	system("pause");
	return 0;
}