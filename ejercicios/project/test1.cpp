#include<vector>
#include<random>
#include"main.hpp"

bool test1(void)
{
    bool test=true;
    std::vector<double> r(2*400);
    std::mt19937 gen(0);
    std::uniform_real_distribution<> dis(0,100);
    int rep=20;

    /*se revisa que al inicializar las partículas en un arreglo de lado 2
      ninguna partícula se salga de la caja, además de verificar que todas 
      las componentes sean distintas, ya que hay probabilidad cero de que
      dos componentes tengan la misma posición.*/
    for(int i=0;i<rep;i++){
        I_state(r,10.0,dis(gen));
        for(long unsigned int i=0;i<r.size();i++){
            if(r[i]>1 || r[i]<-1){
                test=false;
                break;
            }
            if(r[i]==r[i+1]){
                test=false;
                break;
            }
        }
    }
    
    return test;
}
