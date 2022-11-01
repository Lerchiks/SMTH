#include "stdafx.h"
#include <iostream>

void printP(int * Polinom, int deg, const char* prefix ="", int x_0=0 );

int main()
{
	
	int deg = 0;
	do {
		std::cout << "stepen: ";
		std::cin >> deg;
	} while (deg < 0);

	int *Polinom = new int[deg+1];
	std::cout << " " << std::endl;

	for (int i = 0; i < deg + 1; ++i)
	{
		std::cout << "p" << i << ": ";
		std::cin >> Polinom[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;

    int x_0 = 0;
	std::cout << "x_0: ";
	std::cin >> x_0;

	printP(Polinom, deg, "p(x_0): ");

	

	std::cout << std::endl;

	int res = Polinom[0];
	for (int i = 0; i < deg + 1; ++i)
		res = res * x_0 + Polinom[i];

	std::cout << "p_0(x_0): " << res << std::endl;
	delete[] Polinom;
    return 0;
}

void printP(int * Polinom, int deg, const char* prefix, int x_0) {
	std::cout << prefix;
	for (int i = 0; i < deg + 1; ++i){	
		if (Polinom[i] == 0) continue;

		if (Polinom[i] > 0 && i > 0)
			std::cout << '+';
		std::cout << Polinom[i];
		
		if (x_0 == 0) {
			if (deg - i > 1)
				std::cout << "x^" << (deg - i);
			else if (deg - i > 0)
				std::cout << "x";
		}
		else if (x_0>0) {
			if (deg - i > 1)
				std::cout << "(x-" << x_0 << ") ^ " << (deg - i);
			else if (deg - i > 0)
				std::cout << "(x-" << x_0 << ")";
		}
		else {
			if (deg - i > 1)
				std::cout << "(x+" << -x_0 << ") ^ " << (deg - i);
			std::cout << "(x+" << -x_0 << ")";
		}
	}
	std::cout << std::endl;
}
