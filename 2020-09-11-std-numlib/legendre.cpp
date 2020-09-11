#include<iostream>
#include<cmath>

int main(void)
{
    int n=5;
    const double Nmin=-1.0;
    const double Nmax=1.0;
    const double dx=0.01;

    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    
    for(double x=Nmin;x<=Nmax;x+=dx){
        std::cout<<x<<"\t"<<std::legendre(n,x)<<"\n";
    }
    

    return 0;
}
