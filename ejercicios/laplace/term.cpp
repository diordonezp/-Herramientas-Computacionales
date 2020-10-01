#include<cmath>

double a_nm(int n, int m,double a, double x, double y, double z)
{
    double k_nm=M_PI*std::hypot(n,m)/a;
    double term=((std::sinh(k_nm*z)+std::sinh(k_nm*(a-z)))/(n*m*std::sinh(k_nm*a)))*std::sin(n*M_PI*x/a)*std::sin(m*M_PI*y/a);
    
    return term;
}
