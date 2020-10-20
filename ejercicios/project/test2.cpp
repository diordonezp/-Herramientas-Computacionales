#include<vector>
#include<random>
#include"main.hpp"

bool test2(void)
{
    bool test=true;
    std::vector<double> r(2);
    r={0,0};
    
    std::mt19937 gen(0);

    /*se revisa que en cada paso aleatorio se sumen catidades aleatorias
      distintas.*/
    //int sum=0;
    for(int i=1;i<100;i++){
        n_state(r,1,gen);
        if(r[0]==r[1]){
            //sum+=1;
            test=false;
        }
    }
    /*if(sum>50){
        test=false;
        }*/

    return test;
}
