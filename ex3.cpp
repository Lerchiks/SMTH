 
#include <iostream>

int main()
{
int n,k=0, p;
std::cin >> n;

for (int i=0; i < n; ++i)
{
        for(int j=0;j < n-i; ++j)
          std::cout<<" ";

while(k != i)
 {
        std::cout<<"**";
        k = k+1;
             }
std::cout<<'*'<<std::endl;
k = 0;
}

for (int i=n-2; i > 0; --i)
{
p = 2*i;
	for (int j=0; j < n-i; ++j)
       	   std::cout<<" ";
	for(int k = 1+p; k > 0; --k)
	   std::cout << "*";


std::cout<<std::endl;
	
}

}
