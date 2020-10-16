#include<vector>
#include<cmath>
#include"E.hpp"

double E(std::vector<double> r,double l, int m)
{
    double dm=2*(l/m);
    int N=r.size()/2;
    double E=0.0;

    //P será el vector de las m^2 casillas de la grilla 
    std::vector<double> P(m*m);
    
    for(int ii=0;ii<P.size();ii++){
        P[ii]=0.0;
    }

    set_P(r,P,N,l,m,dm);

    for(int i=0;i<P.size();i++){
        if(P[i]!=0){
            E+=P[i]*std::log(P[i]);
        }
    }
    return -E;
}
