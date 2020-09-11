#include<iostream>
#include<random>

int main(void)
{
    int N=20;
    double histo[N]={0.0};
    double a=0.0; double b=1.0;
    double dx=(b-a)/N;
    
    std::mt19937 gen(0); //declarando el generador de números aleatorios
    std::uniform_real_distribution<double> dis(a,b); //números double aleatorios entre 0 y 1
    
    for(int i=0;i<10000;i++){
        double r=dis(gen);
        int aux=int((r-a)/dx);
        histo[aux]+=1;
    }

    for(int i=0;i<N;i++){
        std::cout<<a+i*dx<<"\t"<<histo[i]<<"\n";
    }
    
    return 0;
}
