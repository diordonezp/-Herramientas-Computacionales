#include<iostream>
#include<cmath>
#include"laplace.h"



int main(void)
{
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    double a=1.0;
    double v=2.0;
    double z=0.5;
    
    for(double x=0.0;x<=a;x+=0.1){
        for(double y=0.0;y<=a;y+=0.1){
            std::cout<<x<<"\t"<<y<<"\t"<<phi(x,y,z,a,v)<<"\n";
        }
    }
    
    return 0;
}



