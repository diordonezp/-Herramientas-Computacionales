#include<vector>
#include"E.hpp"

double E(std::vector<double> r,double l, int m)
{
    double dm=2*(l/m);
    
    //P será el vector de las m^2 casillas de la grilla 
    std::vector<double> P(m*m);
    
    //se inicializa P con ceros
    for(int ii=0;ii<P.size();ii++){
        P[ii]=0.0;
    }
    
    /*se rellena P con (la cantidad de partículas que hay en cada celda de
      la grilla)/(la cantidad total de partículas)*/
    set_P(r,P,l,m,dm);
    
    return entropy(P);
}

