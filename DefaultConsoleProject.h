#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

//Use M_PI for PI

//Struct koji sadrzi 2 int (x, y)
struct Vector2i
{
	int x, y;
};

//Struct koji sadrzi 2 float (x, y)
struct Vector2f
{
	float x, y;
};

//Struct koji sadrzi 2 unsigned int (x, y)
struct Vector2u
{
	unsigned int x, y;
};

//Struct koji sadrzi 2 double (x, y)
struct Vector2d
{
	double x, y;
};

//System("pause")
void Pause() { std::cout << std::endl; system("pause"); }
//System("clear")
void Clear() { system("cls"); }

//In Range For Loop
auto coutVector = [&](auto l_vector)
{
	for (auto &i : l_vector)
	{
		std::cout << i;
		std::cout << ", ";
	}
};

//Stvar 2D Pointer to Pointer Array
int** construct2DArray(int l_y, int l_x)
{
	int** arr = new int*[l_y];

	for (int i = 0; i < l_y; i++)
		arr[i] = new int[l_x];

	return arr;
}

//Vraca obrnuti broj od unesenog npr. 123 -> 321
int getReverse(int l_n)
{
	int nRemainder(0);
	int nReverse(0);

	while (l_n != 0)
	{
		nRemainder = l_n % 10;
		nReverse = nReverse * 10 + nRemainder;
		l_n /= 10;
	}
	return nReverse;
}

//Sortira array / polje
void sortArray(int* l_array, int l_size)
{
	std::sort(l_array, l_array + l_size);
}

//Ispisuje array / polje
void coutArray(int* l_array, int l_size)
{
	for (int i = 0; i < l_size; i++)
	{
		std::cout << l_array[i];

		if (i != l_size - 1)
			std::cout << ", ";
	}
}




