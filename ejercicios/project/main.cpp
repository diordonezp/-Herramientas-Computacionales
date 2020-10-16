#include<iostream>
#include<vector>
#include<random>
#include<cmath>
//#include"main.hpp"

void print(std::vector<double> r);
void I_state(std::vector<double> &r,double l, int Iseed);
void n_state(std::vector<double> &r,double l,std::mt19937 &gen);
double E(std::vector<double> r,double l,int i);

int main(void)
{
    double lattice=100.0;//mitad de la longitud de la caja que encierra
    //las partículas
    int N=400;//número de partículas
    int n=1e6;//iteraciones
    int seed=0;//semilla aleatoria para evolución del sistema
    int Iseed=0;//semilla aleatoria para el estado inicial
    int j=8;//númerode casillas por lado de la grilla -> grilla ixi

    std::mt19937 gen(seed);
    
    std::vector<double> r(2*N);
    
    //inicialización de las partículas
    I_state(r,lattice,Iseed);
    
    //evolución del sistema en n pasos de camino aleatorio
    for(int i=0;i<n;i++){
        n_state(r,lattice,gen);
        std::cout<<i<<"\t"<<E(r,lattice,j)<<"\n";
    }
    
    return 0;
}

void print(std::vector<double> r)
{
    for(int i=0;i<r.size();i+=2){
        std::cout<<r[i]<<"\t"<<r[i+1]<<"\n";
    }
}

void I_state(std::vector<double> &r,double l, int Iseed)
{
    std::mt19937 gen(Iseed);
    std::uniform_real_distribution<> dis(-l/10,l/10);

    for(int i=0;i<r.size();i++){
        r[i]=dis(gen);
    }
}

void n_state(std::vector<double> &r,double l,std::mt19937 &gen)
{
    double dl=0.5;
    std::uniform_real_distribution<> dis(-dl,dl);
    
    for(int i=0;i<r.size();i++){
        r[i]+=dis(gen);
        if(r[i]>l){
            r[i]=l;
        }
        if(r[i]<-l){
            r[i]=-l;
        }
    }
}

double E(std::vector<double> r,double l, int m)
{
    double dm=2*(l/m);
    int N=r.size()/2;
    double E=0.0;

    //P será el vector de las m^2 casillas de la grilla 
    std::vector<double> P(m*m);
    
    for(int ii=0;ii<P.size();ii++){
        P[ii]=0.0;
    }

    //cada elemento de P cuenta cuantas la probabilidad (partículas en i/N) hay en cada casilla
    for(int k=0;k<r.size();k+=2){
        int ii=0;
        int jj=0;
        for(int i=0;i<m;i++){
            if(r[k]>=(-l+i*dm) && r[k]<(-l+i*dm+dm)){
                ii=i; 
            }
        }
        for(int i=0;i<m;i++){
            if(r[k+1]>=(-l+i*dm) && r[k+1]<(-l+i*dm+dm)){
                jj=i;
            }
        }
        P[jj*m+ii]+=1.0/N;
    }

    for(int i=0;i<P.size();i++){
        if(P[i]!=0){
            E+=P[i]*std::log(P[i]);
        }
    }
    return -E;
}
