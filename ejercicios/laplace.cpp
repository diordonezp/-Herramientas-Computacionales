#include<iostream>
#include<cmath>

double phi(double x,double y,double z,double a,double v);
double a_nm(int n, int m,double a, double x, double y, double z);

int main(void)
{
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);

    double a=1.0;
    double v=2.0;
    double z=0.0;
    
    for(double x=0.0;x<=a;x+=0.1){
        for(double y=0.0;y<=a;y+=0.1){
            std::cout<<x<<"\t"<<y<<"\t"<<phi(x,y,z,a,v)<<"\n";
        }
    }
    
    return 0;
}

double a_nm(int n, int m,double a, double x, double y, double z)
{
    double k_nm=M_PI*std::hypot(n,m)/a;
    double term=((std::sinh(k_nm*z)+std::sinh(k_nm*(a-z)))/(n*m*std::sinh(k_nm*a)))*std::sin(n*M_PI*x/a)*std::sin(m*M_PI*y/a);
    
    return term;
}

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
