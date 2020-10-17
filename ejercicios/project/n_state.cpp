#include<random>
#include<vector>

void n_state(std::vector<double> &r,double l,std::mt19937 &gen)
{
    double dl=0.5;
    std::uniform_real_distribution<> dis(-dl,dl);
    
    /*a cada elemento del vector, se suma una cantidad aleatoria pequeña
      y se verifica que el nuevo elemento no se salga de las paredes, en
      tal caso, se le devuelve a la pared*/
    for(int i=0;i<r.size();i++){
        r[i]+=dis(gen);
        if(r[i]>l){
            r[i]=l;
        }
        if(r[i]<-l){
            r[i]=-l;
        }
    }
}
