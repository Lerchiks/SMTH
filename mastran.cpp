#include <iostream>

int main() {
	unsigned int n;
	std::cin >> n;
	char bin[65] = "";
	//скажем, что мы берём 65ый символ\n для окончания строки массива
	int indx = 0;
	
	while (n){
		bin[indx] = '0' + (n % 2);
		++indx;
		n >>= 1; // n /= 2;
	}
	
	if (indx == 0){
	bin[0] = '0';
	++indx;
	}
	
	bin[indx] = '\0';
	std::cout << bin << std::endl;
	
	for (int i = 0, j = indx - 1; i <= j ; ++i, --j )
	    std::swap(bin[i], bin [j]);
	    
	std::cout << bin << std::endl;    
	return 0;
}
