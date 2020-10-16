#include<random>
#include<vector>

void n_state(std::vector<double> &r,double l,std::mt19937 &gen)
{
    double dl=0.5;
    std::uniform_real_distribution<> dis(-dl,dl);
    
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
