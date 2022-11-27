#include <iostream>
#include <fstream>

double Determinant(double**, int, int);
void DeletM(double**, int);
bool Triang(double**, int, int);
bool obrDiagM(double**, int, int);
bool Diag(double**, int, int);
double** invM(double**, int, int);
double** HaveDiag(double**,double**, int, int);

int main(int argc, char* argv[]) {
	
	char inputFile[256] = "test.txt";
	if (argc > 1) {
		strcpy_s(inputFile, argv[2]);
	}

	char outputFile[256] = "output.txt";
	if (argc > 2) {
		strcpy_s(outputFile, argv[3]);
	}
	
	std::ifstream inFile(inputFile);

	std::ofstream outFile(outputFile);

	int n = 0, m = 0, rev = 0, ind = 0;
	char ch = inFile.get();

	rev = ch;
	if (rev != ' ') {
		ind = rev - '0';
		ind *= 10;
	}
	while ((ch = inFile.get()) != '\n') {
		if (ch != ' ') {
			ind += (ch - '0');
			ind *= 10;
		}
		else {
			if (rev != ' ') {
				ind /= 10;
				n = ind;
				ind = 0;
			}
		}
		rev = ch;
	}
	m = ind/10;

	if (m != n) {
		outFile.put('e');
		outFile.put('r');
		outFile.put('r');
		outFile.put('o');
		outFile.put('r');
		return 0;
	}

	double** Matrix;
	Matrix = new double* [n];
	for (int i = 0; i < n; ++i) {
		Matrix[i] = new double[m];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			Matrix[i][j] = 0.0;
		}
	}

	int sign = 1;
	bool t = false;
	int row = 0, col = 0;
	ch = inFile.get();
	rev = ch;
	int h = 0;

	if (rev != ' ' && rev != '\n' && rev != '-' && rev != '.') {
		h = rev - '0';
		h *= 10;
	}
	else if (rev == '-') {
		sign = -1;
	} 

	while ((ch = inFile.get()) != EOF) {

		if (ch == '-') {
			sign = -1;
		}
		if (ch != ' ' && ch != '\n' && ch != '-' && ch != '.') {
			h += (ch - '0');
			h *= 10;
		}
		else {
			if (rev != ' ' && rev != '\n' && rev != '-' && rev != '.') {
				h /= 10;
				h *= sign;
				Matrix[row][col] = h;

				if (col + 1 == m) {
					col = 0;
					++row;
				}
				else {
					++col;
				}
				h = 0;
				sign = 1;
			}
		}
		if (ch == '-') {
			sign = -1;
		}
		if (ch == '.') {
			t = true;
		}
		if (ch == '0' && rev == '.') {
			continue;
		}
		
		rev = ch;
	}

	if (!t) {
		h /= 10;
		Matrix[n - 1][m - 1] = h;
	}

	double det = 0;
	bool f = false;

	if (Triang(Matrix, n, m)) {
		row = 0;
		det = 1;
		while (row != n) {
			det *= Matrix[row][row];
			++row;
		}
		f = true;
	}
	

	int shift = 1;
	if (!f) {
		if (obrDiagM(Matrix, n, m)) {
			det = 1;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					if (i + j == n - 1) {
						if ((n - 1) % 2 != 0) {
							shift = -1;
						}
						det *= (Matrix[i][j] * shift);
					}
				}
			}
		}
		else {
			det = Determinant(Matrix, n, m);
		}
	}
	std::cout << det;

	double** InvMatrix = new double* [n];
	for (int i = 0; i < n; ++i) {
		InvMatrix[i] = new double[m];
	}

	if (det == 0 && argv[1] == "-inv") {
		outFile.put('s');
		outFile.put('i');
		outFile.put('n');
		outFile.put('g');
		outFile.put('u');
		outFile.put('l');
		outFile.put('a');
		outFile.put('r');
	}
	else {
		if (Diag(Matrix, n, m)) {
			InvMatrix = Matrix;
		}
		else {
			InvMatrix = invM(Matrix, n, m);
		}
	}

	if (argv[1] == "-det") {
		outFile.put((char)det);
	}
	else if (argv[1] == "-inv") {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				outFile.put((char)InvMatrix[i][j]);
				if (t) {
					outFile.put('.');
					outFile.put('0');
				}
				outFile.put(' ');
			}
			outFile.put('\n');
		}
	}
	inFile.close();
	outFile.close();
	DeletM(Matrix, n);
	DeletM(InvMatrix, n);
	
	return 0;
}

bool Diag(double** M, int row, int col) {
	bool temp = true;
	for (int i = 0; i < row; ++i) {
		for (int j = i + 1; j < col; ++j) {
			if (M[i][j] != 0) {
				temp = false;
				break;
			}
		}
		if (!temp) {
			return false;
		}
	}
	if (temp) {
		for (int i = 1; i < row; ++i) {
			for (int j = 0; j < i; ++j) {
				if (M[i][j] != 0) {
					temp = false;
					break;
				}
			}
			if (!temp) {
				break;
			}
		}
		if (temp) {
			return true;
		}
	}
	return false;
}
bool Triang(double** M, int row, int col) {
	bool temp = true;
	for (int i = 0; i < row; ++i) {
		for (int j = i+1; j < col; ++j) {
			if (M[i][j] != 0) {
				temp = false;
				break;
			}
		}
		if (!temp) {
			break;
		}
	}
	if (temp) {
		return true;
	}
	temp = true;
	for (int i = 1; i < row; ++i) {
		for (int j = 0; j < i; ++j) {
			if (M[i][j] != 0) {
				temp = false;
				break;
			}
		}
		if (!temp) {
			break;
		}
	}
	if (temp) {
		return true;
	}
	else {
		return false;
	}
}
bool obrDiagM(double** M, int row, int col) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (i + j != row - 1){
				if (M[i][j] != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

double Determinant(double** M, int row, int col) {

	double** p = new double* [row-1];
	for (int i = 0; i < row - 1; ++i) {
		p[i] = new double[col - 1];
	}

	double sum = 0, shift = 1, k = 0;
	if (row == 2) {
		DeletM(p, row - 1);
		return M[0][0] * M[row - 1][col - 1] - M[0][col - 1] * M[row - 1][0];
	}
	else {
		std::cout << "-----------" << std::endl;
			for (int i = 0; i < row; ++i) {
				if (M[0][i] == 0) {
					shift *= -1;
					continue;
				}
				for (int g = 1, rows = 0; g < row; ++g, ++rows) {
					for (int j = 0, cols = 0; j < col; ++j, ++ cols) {
						if (j == i) {
							--cols;
							continue;
						}
						else {
							p[rows][cols] = M[g][j];
						}
						std::cout << M[g][j] << " ";
					}
					std::cout << std::endl;
				
				} 	std::cout << "-----------" << std::endl;
				k = M[0][i];
				std::cout << "*" << k << std::endl;
				sum += (shift * k * (Determinant(p, row - 1, col - 1)));
				shift *= -1;
			}
	}
	return sum;
}

double** invM(double** M, int row, int col) {
	double** E = new double* [row];
	for (int i = 0; i < row; ++i) {
		E[i] = new double[col];
	}

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (i == j) {
				E[i][j] = 1;
			}
			else {
				E[i][j] = 0;
			}
		}
	}
	HaveDiag(M, E, row, col);;

	double p = 0;
	int k = 0;
	for (int i = 0; i < row - 1; ++i) {

		for (int i_2 = i + 1; i_2 < row; ++i_2) {
			if (M[i][k] != 0) {
				p = (M[i_2][k] / M[i][k]);
			}
			else {
				p = 1;
			}
			for (int j = 0; j < col; ++j) {
				M[i_2][j] -= (p * M[i][j]);
				E[i_2][j] -= (p * E[i][j]);
			}
		}
		HaveDiag(M, E, row, col);

		++k;
	}	

	for (int i = 0; i < row - 1; ++i) {
		for (int i_2 = i + 1; i_2 < row; ++i_2) {
			p = (M[i][i_2] / M[i_2][i_2]);

			for (int j = 0; j < col; ++j) {
				M[i][j] -= (p * M[i_2][j]);
				E[i][j] -= (p * E[i_2][j]);
			}
		}
	}
	
	for (int i = 0; i < row; ++i) {
		if (M[i][i] != 1) {
			p = M[i][i];
			for (int g = 0; g < row; ++g) {
				if (M[i][g] != 0) {
					M[i][g] /= p;
				}
				E[i][g] /= p;
			}
		}
	}
	return E;
}
double** HaveDiag(double** M, double ** E, int row, int col) {
	int k = 1;
	for (int i = 0, j = 0; i < row; ++i, ++ j) {
		if (M[i][j] == 0 && i != row - 1) {
			while (M[i+k][j] == 0) {
				++k;
			}
			if (M[i+k][j] == 0) {
				k = -1;
			}
				for (int h = 0; h < col; ++h) {
					M[i][h] -= M[i + k][h];
					E[i][h] -= E[i + k][h];
				}
		}else if (i == row - 1 && M[i][j] == 0) {
			for (int h = 0; h < col; ++h) {
				M[i][h] -= M[i - 1][h];
				E[i][h] -= E[i - 1][h];
			}
		}
	}
	return M, E;
}

void DeletM(double** M, int row) {
	for (int i = 0; i < row; ++i) {
		delete[] M[i];
	}
	delete[] M;
};
