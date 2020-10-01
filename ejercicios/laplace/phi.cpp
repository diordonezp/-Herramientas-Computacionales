#include<cmath>
#include"laplace.h"

double phi(double x,double y,double z,double a,double v)
{
    double sum=0.0;

    for(int n=1;n<=100;n+=2){
        for(int m=1;m<=200;m+=2){
            sum+=a_nm(n,m,a,x,y,z);
        }
    }
    sum=16*v/std::pow(M_PI,2)*sum;
    
    return sum;
}
