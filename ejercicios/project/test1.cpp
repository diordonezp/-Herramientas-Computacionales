#include<iostream>
#include<random>
#include"main.hpp"

int main(void)
{
    std::vector<double> r(2);
    r={0,0};

    std::mt19937 gen(0);

    int sum=0;
    for(int i=1;i<100;i++){
        n_state(r,1,gen);
        if(r[0]==r[1]){
            sum+=1;
        }
    }
    if(sum>50){
        std::cerr<<"ALGO NO ANDA BIEN CON LA GENERACIÓN DE NÚMEROS ALEATORIOS.\n";
    }
    else{std::cout<<"PASSED.\n";}

    return 0;
}
