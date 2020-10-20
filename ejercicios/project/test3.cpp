#include<vector>
#include<random>
#include"main.hpp"
#include"E.hpp"

bool test3(void)
{
    std::vector<double> r(2);
    r={0,0};
    bool test=true;

    std::mt19937 gen(0);

    /*se revisa que la entropía de una arreglo de una partícula sea siempre
      iguala cero.*/
    for(int i=0;i<20;i++){
        n_state(r,1,gen);
        if(E(r,1,8)!=0){
            test=false;
        }
    }

    return test;
}
