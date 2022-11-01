#include <iostream>
//для time
#include <time.h>
// #include <ctime>


int main(){
    
    srand((unsigned int)time(NULL)); //прочитай описание данной функции если забудешь))
    //обновление для рандома чтобы числа были разными
    int n = 0, Maxsum = 0;
    
    do{
        std::cout << "ur size: ";
        std::cin >> n;
    }while (n < 1);
    
    int *M = new int [n]; //указатель + иницилизация;

    /*
//не комбинированный вид
    int *M;
    M = new int [n];
    */
    
    if (!M /*M == 0*/)
    std::cout << "err " << std::endl;
    
    
    for (int i = 0; i < n; ++i){
        M[i] = 100 +  rand()%900; //[100; 999]
    }
    
    for (int i = 0; i < n; ++i){
        std::cout << M[i] << " ";    
    }
    std::cout << std::endl;
    
    if (n >= 2){
        for (int i = 1; i < n; ++i){
            Maxsum = std::max(M[i]+M[i-1],Maxsum);
    }
    
        for (int i = 1; i < n; ++i){
            if (M[i] + M[i-1] == Maxsum){
                std::cout << M[i-1] <<" "<< M[i];
                break;
                }
        }
    }
    
    delete[] M; 
    
    // мы не знаем сколько эл ибо он сам определяет занимаемую память и очищает её
    // ВСЕГДА УДАЛЯТЬ ПАМЯТЬ !!!!!!!!!
    
return 0;    
}
