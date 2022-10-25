#include <iostream>

int main()
{
	unsigned int n = 0;
	std::cin >> n;
	unsigned int  a = n, bin_a;
	int su = 0, pr = 1;
    unsigned int shift;	

	while (a)
	{
		su += a%10;
		pr *= a%10;
		a /= 10;
	}
	std::cout << "sum = " << su << " pr = " << pr << std::endl;
    
    shift = 1;
    while (shift <= n)
        shift *= 2;
    
    a = n;
    
    shift /= 2;
    
    while (shift)
    {
        std::cout << a / shift;
        a %= shift;
        shift /= 2;
        
    }

//00111010101 
	return 0;
}
