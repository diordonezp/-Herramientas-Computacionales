# include <iostream>
# include <cmath>

double sin_pade(double x);
double sin_aux(double u);

int main(void)
{
    std::cout.precision(16);
    std::cout.setf(std::ios::scientific);

    for(double x=0.01;x<=2*M_PI;x+=0.01){
        std::cout<<x<<"\t"<<std::fabs(sin_pade(x)-std::sin(x))/std::sin(x)<<"\n";
        //std::cout<<x<<"\t"<<sin_pade(x)<<"\n";
    }
    
    return 0;
}

double sin_pade(double x)
{
    double sin_x=0.0;

    if(x>M_PI/2 && x<=3*M_PI/2){
        x=M_PI-x;
    }

    if(x>3*M_PI/2 ){
        x=x-2*M_PI;
    }
    
    if(std::fabs(x)<=M_PI/6){
        sin_x=sin_aux(x);
    }

    if(std::fabs(x)<10e-8){
        sin_x=x;
    }

    if(std::fabs(x)>M_PI/6){
        double sin_u=sin_aux(x/3);
        sin_x=(3-4*std::pow(sin_u,2))*sin_u;
    }
    
    return sin_x;
}

double sin_aux(double u)
{
    double sin_u=0.0;

    double A=u*(1-(29593*std::pow(u,2)/207636)+(34911*std::pow(u,4)/7613320)-(479249*std::pow(u,6)/11511339840));
    double B=(1+(1671*u*u/69212)+(97*std::pow(u,4)/351384)+(2623*std::pow(u,6)/1644477120));
        

    sin_u=A/B;
             

    return sin_u;
}
