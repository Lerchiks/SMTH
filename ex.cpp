#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

double** HaveDiag(double**, double**, int, int);
double Determinant(double**, int, int);
void DeletM(double**, int);
bool Triang(double**, int, int);
double** invM(double**, double**, int, int);


int main(int argc, char* argv[]) {

	if (argc < 4) {
		return 1;
	}
	char* inputFile = argv[2];
	char* outputFile = argv[3];

	std::ifstream inFile(inputFile);
	std::ofstream outFile(outputFile);

	int n = 0, m = 0, ind = 0;
	double rev = 0.0;
	char ch = inFile.get();
	int g = 0;

	//размер
	g = ch;
	if (g != ' ') {
		ind = g - '0';
		ind *= 10;
	}
	while ((ch = inFile.get()) != '\n') {
		if (ch != ' ') {
			ind += (ch - '0');
			ind *= 10;
		}
		else {
			if (g != ' ') {
				ind /= 10;
				n = ind;
				ind = 0;
			}
		}
		g = ch;
	}
	m = ind / 10;


	// проверка размера
	char error[6] = "error";
	if (m != n) {
		outFile << error;
		return 0;
	}

	double** Matrix = new double* [n];
	for (int i = 0; i < n; ++i) {
		Matrix[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			Matrix[i][j] = 0.0;
		}
	}
	
	//заполнение матрицы из файла
	int sign = 1;
	bool t = false;
	bool zer = false;
	int row = 0;
	int col = 0;
	ch = inFile.get();
	rev = ch;
	double h = 0.0;
	bool pzer = false;

	if (rev != ' ' && rev != '\n' && rev != '-' && rev != '.') {
		h = static_cast<double>(rev - '0');
		h *= 10;
	}
	else if (rev == '-') {
		sign = -1;
	}

	double** p = new double* [n];
	for (int i = 0; i < n; ++i) {
		p[i] = new double[m];
	}

	while ((ch = inFile.get()) != EOF) {
		if (ch == '.') {
			p[row][col] = 1;
			pzer = true;
		}
		if (ch == '-') {
			sign = -1;
		}
		if (ch != ' ' && ch != '\n' && ch != '-' && ch != '.') {
			h += static_cast<double>(ch - '0');
			h *= 10.0;
		}
		else {
			if (rev != ' ' && rev != '\n' && rev != '-' && rev != '.') {
				h /= 10.0;
				h *= sign;
				Matrix[row][col] = static_cast<double>(h);
				if (col + 1 == m) {
					col = 0;
					++row;
				}
				else {
					++col;
				}
				h = 0.0;
				sign = 1;
				t = false;
			}
		}
		if (ch == '-') {
			sign = -1;
		}

		if (ch == '0' && rev == '.') {
			t = true;
			continue;
		}

		rev = static_cast<double> (ch);
	}
	if (!t) {
		h /= 10.0;
		Matrix[n - 1][m - 1] = static_cast<double > (h);
	}


	double det = 0.0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (Matrix[i][j] != 0) {
				zer = false; 
				break;
			}
		}
		if (zer) {
			det = 0.0;
			if (argv[1][1] == 'i') {
				outFile << "singular";
				DeletM(Matrix, n);
				DeletM(p, n);
				return 0;
			}
			else {
				outFile << det;
				if (pzer) {
					outFile << ".0";
				}
				DeletM(Matrix, n);
				DeletM(p, n);
				return 0;
			}
		}
	}

	// единичная
	double** E = new double* [n];
	for (int i = 0; i < n; ++i) {
		E[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i != j) {
				E[i][j] = 0.0;
			}
			else {
				E[i][j] = 1.0;
			}
		}
	}
	double** M_cop = new double* [n];
	for (int i = 0; i < n; ++i) {
		M_cop[i] = new double[m];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			M_cop[i][j] = Matrix[i][j];
		}
	}
	det = Determinant(Matrix, n, m);

	std::cout << '\n';
	std::cout << "Matrix: \n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cout << static_cast<double>(Matrix[i][j]) << " ";
		}
		std::cout << std::endl;
	}
	if (det != 0) {
		E = invM(M_cop, E, row, col);
	}
	std::cout << "E: \n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cout << static_cast<double>(E[i][j]) << " ";
		}
		std::cout << std::endl;
	}


	inFile.close();
	outFile.close();
	DeletM(Matrix, n);
	DeletM(E, n);
	DeletM(p, n);
	DeletM(M_cop, n);
	return 0;
}


bool Triang(double** M, int row, int col) {
	bool temp = true;
	for (int i = 0; i < row; ++i) {
		for (int j = i + 1; j < col; ++j) {
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

double Determinant(double** M, int row, int col) {
	int j = 0;
	double temp = 0;
	int shift = 0;
	double** E = new double*[row];
	for (int i = 0; i < row; ++i) {
		E[i] = new double[col];
	}

	for (int i = 0; i < row; ++i) {
		if (M[i][i] == 0 && i != row - 2) {
			if (i + 1 >= row) {
				continue;
			}
			else {
				j = i + 1;
			}
			while (j != row - 1 || M[j][i] != 0) {
				if (M[j][i] != 0 && j != i) {
					for (int k = 0; k < col; ++k) {
						temp = M[i][k];
						M[i][k] = M[j][k];
						M[j][k] = temp;
					}
					shift += 1;;
				}
				if (j + 1 >= row) {
					break;
				}
				else {
					++j;
				}
			}
		}
	}
	int k = 0;
	double p = 0.0;
	double det = 1.0;
	if (!Triang(M, row, col)) {
		while (!Triang(M, row, col)) {
			k = 0;
			for (int i = 0; i < row - 1; ++i) {

				for (int i_2 = i + 1; i_2 < row; ++i_2) {
					if (M[i_2][k] == 0) {
						continue;
					}
					else if (M[i][k] != 0) {
						p = (M[i_2][k] / M[i][k]);
					}
					else if (M[i][k] == 0) {
						p = 1.0;
					}
					for (int j = 0; j < col; ++j) {
						M[i_2][j] -= (p * M[i][j]);
						if (M[i_2][j] < 1e-10 && M[i_2][j] > -1 * (1e-10)) {
							M[i_2][j] = 0.0;
						}
					}

				}
				
				HaveDiag(M,E, row, col);
				std::cout << '\n';
				for (int h = 0; h < row; ++h) {
					for (int g = 0; g < col; ++g) {
						std::cout << M[h][g] << " ";
					}
					std::cout << '\n';
				}
				++k;
			}
		}
	}
	for (int i = 0, j = 0; i < row; ++i, ++j) {
		det *= M[i][j];
	}

	if (shift != 0) {
		shift = (shift % 2 == 1) ? -1 : 1;
		det *= shift;
	}
	std::cout << det;
	DeletM(E, row);
	return det;
}


double** invM(double** M, double** E, int row, int col) {

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
				if (M[i][j] < 1e-10 && M[i][j] > -1 * (1e-10)) {
					M[i][j] = 0.0;
				}
				if (E[i][j] < 1e-10 && E[i][j] > -1 * (1e-10)) {
					E[i][j] = 0.0;
				}
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
				if (M[i][g] < 1e-10 && M[i][g] > -1 * (1e-10)) {
					M[i][g] = 0.0;
				}
				E[i][g] /= p;
				if (E[i][g] == -0) {
					E[i][g] *= -1;
				}
				if (E[i][g] < 1e-10 && E[i][g] > -1 * (1e-10)) {
					E[i][g] = 0.0;
				}
			}
		}
	}

	return E;
}
double** HaveDiag(double** M,  double **E, int row, int col) {
	int k = 1;
	for (int i = 0, j = 0; i < row; ++i, ++j) {
		if (M[i][j] == 0 && i != row - 1) {
			while (M[i + k][j] == 0 && (k + i + 1) != row) {
				++k;
			}
			if (M[i + k][j] == 0 && i != 0) {
				--k;
				while (k + i + 1 != row && M[i + k][j] == 0)
					--k;
			}
			for (int h = 0; h < col; ++h) {
				M[i][h] -= M[i + k][h];
				if (M[i][h] < 1e-10 && M[i][h] > -1 * (1e-10)) {
					M[i][h] = 0.0;
				}
				E[i][h] -= E[i + k][h];
				if (E[i][h] < 1e-10 && E[i][h] > -1 * (1e-10)) {
					E[i][h] = 0.0;
				}
			}
		}
		else if (i == row - 1 && M[i][j] == 0) {
			for (int h = 0; h < col; ++h) {
				M[i][h] -= M[i - 1][h];
				if (M[i][h] < 1e-10 && M[i][h] > -1 * (1e-10)) {
					M[i][h] = 0.0;
				}
				E[i][h] -= E[i - 1][h];
				if (E[i][h] < 1e-10 && E[i][h] > -1 * (1e-10)) {
					E[i][h] = 0.0;
				}
			}
		}
		k = 1;
	}
	return M;
}




void DeletM(double** M, int row) {
	for (int i = 0; i < row; ++i) {
		delete[] M[i];
	}
	delete[] M;
}
