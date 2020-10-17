#include<vector>
#include<random>

void I_state(std::vector<double> &r,double l, int Iseed)
{
    std::mt19937 gen(Iseed);
    std::uniform_real_distribution<> dis(-l/10,l/10);
    
    /*se le asigna a cada elemento un valor aleatorio dentro de una caja
      de dimensión l/5*l/5*/
    for(int i=0;i<r.size();i++){
        r[i]=dis(gen);
    }
}
