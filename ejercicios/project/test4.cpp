#include<vector>
#include<iostream>
#include"E.hpp"

bool test4(void)
{
    std::cout.precision(17);
    bool test=true;
    double l=2.0;
    int m=2;
    double dm=2*(l/m);
    
    std::vector<double> r(2*(13));
    r={-2,-2,0,-2,2,-2,
       -1,-1,1,-1,
       -2,0,0,0,2,0,
       -1,1,1,1,
       -2,2,0,2,2,2};

    std::vector<double> P(m*m);
    for(long unsigned int i=0;i<P.size();i++){
        P[i]=0;
    }
    std::vector<double> Paux(m*m);
    Paux={5.0/13.0,3.0/13.0,3.0/13.0,2.0/13.0};

    set_P(r,P,l,m,dm);

    for(long unsigned int i=0;i<P.size();i++){
        if(P[i]!=Paux[i]){
            test=false;
        }
    }

    m=4;
    dm=2*(l/m);

    r.resize(2*(41));
    P.resize(m*m);
    Paux.resize(m*m);

    for(long unsigned int i=0;i<P.size();i++){
        P[i]=0;
    }
    Paux={5.0/41.0,3/41.0,3.0/41.0,3.0/41.0,3.0/41.0,2.0/41.0,2.0/41.0,2.0/41.0,3.0/41.0,2.0/41.0,2.0/41.0,2.0/41.0,3.0/41.0,2.0/41.0,2.0/41.0,2.0/41.0};
    
    r={-2,-2,-1,-2,0,-2,1,-2,2,-2,
       -1.5,-1.5,-0.5,-1.5,0.5,-1.5,1.5,-1.5,
       -2,-1,-1,-1,0,-1,1,-1,2,-1,
       -1.5,-0.5,-0.5,-0.5,0.5,-0.5,1.5,-0.5,
       -2,0,-1,0,0,0,1,0,2,0,
       -1.5,0.5,-0.5,0.5,0.5,0.5,1.5,0.5,
       -2,1,-1,1,0,1,1,1,2,1,
       -1.5,1.5,-0.5,1.5,0.5,1.5,1.5,1.5,
       -2,2,-1,2,0,2,1,2,2,2};


    set_P(r,P,l,m,dm);

    for(long unsigned int i=0;i<P.size();i++){
        if(P[i]!=Paux[i]){
            test=false;
        }
    }
    
    return test;
}
