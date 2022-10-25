#include <iostream>

int main()
{
	unsigned int n = 0;
	std::cin >> n;
	unsigned int  a = n;
	int su = 0, pr = 1;
    unsigned int shift = 1;	

	while (a)
	{
		su += a%10;
		pr *= a%10;
		a /= 10;
	}
	std::cout << "sum = " << su << " pr = " << pr << std::endl;
    
    
    
    while (shift <= n && shift != 0)
        shift <<= 1;
    
    if (shift ==0)
    {
    std::cout << 1;
    a = n - (1 << 31);
    shift = 1 << 31;
    }
    else
    {
    a = n;
    }
    
    shift >>= 1;
    
    
    while (shift)
    {
        std::cout << a / shift;
        a %= shift;
        shift >>= 1; //shift /= 2;
    }
    
    

//00111010101 
	return 0;
}
