#include <iostream>

int main(){
int n;
 std::cin >> n;

for (int i=0;i<n+1;++i)
{
for (int j=0;j < i; ++j){
	std::cout<<'*';
}
std::cout<<std::endl;
}

std::cout<<std::endl;

}
