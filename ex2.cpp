#include <iostream>
int main()
{
int n,k=0 ,f = 0;

std::cin >> n;

for (int i=0; i < n+1; ++i)
{
	for(int j=0;j < n-i; ++j)
	  std::cout<<" ";

while(k != i)
 {
	std::cout<<"**";
	k = k+1;
	     }
std::cout<<'*';

k = 0;

std::cout<<std::endl;
}

}
