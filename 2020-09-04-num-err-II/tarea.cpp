#include<iostream>
#include<cmath>

float f(float x);
float f_mod(float x);


int main(int argc, char *argv[])
{
    std::cout.precision(8);
    std::cout.setf(std::ios::scientific);

    int eps=std::atoi(argv[1]);
    
    for(int i=0;i<=eps;i++){
        std::cout<<1.0*i/eps<<"\t"<<f(1.0*i/eps)<<"\t"
                 <<f_mod(1.0*i/eps)<<"\n";
    }
    
    return 0;
}

float f(float x)
{
    return 5-std::sqrt(25+std::pow(x,2));
}

//función modificada para mejorar la precisión en valores pequeños de x,
//queremos evitar hacer restas entre números muy cercanos.
float f_mod(float x)
{
    return -std::pow(x,2)/(5+std::sqrt(25+std::pow(x,2)));
}
