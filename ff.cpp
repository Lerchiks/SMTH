#include <iostream>

int main()
{
    // A = 10; B = 11; C = 12; D = 13; E = 14; F = 15; G = 16;
    long long int n;
    int a, j=0;
    std::cin >> n >> a;
    unsigned int shift = 1;
    
    while (shift <= n && shift != 0)
    shift *= a;
    
    shift /= a;
    
    std::cout << shift << std::endl;
    
    
    while (shift)
    {
        j = n / shift;
        
        if (j >= 10)
            switch (j)
            {
                case 10: {std::cout << "A"; break;}
                case 11: {std::cout << "B"; break;}
                case 12: {std::cout << "C"; break;}
                case 13: {std::cout << "D"; break;}
                case 14: {std::cout << "E"; break;}
                case 15: {std::cout << "F"; break;}
                case 16: {std::cout << "G"; break;}    
                }
        else   
        std::cout << j;
        
        n %= shift;
        shift /= a;
    }
    
    return 0;    
}
