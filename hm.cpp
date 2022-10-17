#include <iostream>

double st(double a, int b)
{
	double step = 1;
	while (b > 0)
	{
		step *= a;
		--b;
	}
	return step;
}

int main()
{
	double x, y;
	int width = 41;
	int height = 21;
	double f = 0;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			x = 1.5 - 3.0 * j / (width - 1);
			y = 1.5 - 3.0 * i / (height - 1);
		
			f = st(st(x, 2) + st(y, 2) - 1, 3) - st(x, 2) * st(y, 3);
			std::cout << (f <= 0) ? '*' : '.';
			
		}
		std::cout << std::endl;
	}
}
