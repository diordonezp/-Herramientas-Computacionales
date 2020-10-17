#include<iostream>
#include<vector>
#include<random>
#include"main.hpp"
#include"E.hpp"

int main(void)
{
    std::vector<double> r(2*400);
    
    //TEST1: INICIALIZACIÓN==============================================================
    std::cout<<"test1: las partículas se inicializaron bien:\n";
    bool test=true;
    I_state(r,10.0,10);
    for(int i=0;i<r.size();i++){
        if(r[i]>1 || r[i]<-1){
            std::cerr<<"VECTOR DE PARTÍCULAS MAL INICIALIZADO: FUNCIÓN I_state.\n";
            test=false;
            break;
        }
    }
    if(test==true){std::cout<<"test1: PASSED.\n";}
    //====================================================================================

    //TEST2: PASO ALEATORIO===============================================================
    std::cout<<"test2: componentes son aleatorias:\n";
    r.resize(2);
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
        std::cerr<<"ALGO NO ANDA BIEN CON LA GENERACIÓN DE NÚMEROS ALEATORIOS: FUNCIÓN n_state.\n";
    }
    else{std::cout<<"test2: PASSED.\n";}
    //====================================================================================

    return 0;
}
