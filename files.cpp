// ulconvert.cpp : Defines the entry point for the console application.
#include "stdafx.h"

//#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{

	char inputFile[256] = "readme.txt";
	if (argc > 1) {
		strcpy_s(inputFile, argv[1]);
	}
	else {
		std::cout << "Input FileName: ";
		std::cin.getline(inputFile, 256);
	}



	char outputFile[256] = "output.txt";
	if (argc > 2) {
		strcpy_s(outputFile, argv[2]);
	}
	else {
		std::cout << "output FileName: ";
		std::cin.getline(outputFile, 256);
		if (strlen(outputFile) == 0) {
			strcpy_s(outputFile, "output.txt");
		}
	}

	std::ifstream inFile(inputFile);
	if (!inFile) {
		std::cerr << "can not read " << inputFile << std::endl;
		return 0;
	}

	std::ofstream outFile(outputFile);
	if (!outFile) {
		std::cerr << "can not write to file " << outputFile << std::endl;
		inFile.close();
		return 2;
	}

	int ch;
	while ((ch = inFile.get()) != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			outFile.put('A' + (ch - 'a'));
		}
		else if (ch >= 'A' && ch <= 'Z') {
			outFile.put('a' + (ch - 'A'));
		}
		else if (ch >= '0' && ch <= '9') {
			outFile.put('*');
		}
		else {
			outFile.put(ch);
		}
	}

	inFile.close();
	outFile.close();

	return 0;
}
