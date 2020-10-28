#include<iostream>
#include<fstream>
#include<vector>
#include<random>
#include<chrono>
#include"main.hpp"

void time(int Nmax,double lattice,int n,int seed,int Iseed,int j);

int main(void)
{
    std::cout.precision(15);std::cout.setf(std::ios::scientific);
    std::ifstream fin("instructions/P_time.txt");

    int Nmax=0;;//máximo número del tamaño del sistema
    fin>>Nmax;
    double lattice=0.0;//mitad de la longitud de la caja que encierra
    //las partículas
    fin>>lattice;
    int n=0;//iteraciones
    fin>>n;
    int seed=0;//semilla aleatoria para evolución del sistema
    fin>>seed;
    int Iseed=0;//semilla aleatoria para el estado inicial
    int j=8;//número de casillas por lado de la grilla -> grilla jxj

    for(int N=1;N<=Nmax;N+=20){
        time(N,lattice,n,seed,Iseed,j);
    }
    
    fin.close();
    return 0;
}

void time(int N,double lattice,int n,int seed,int Iseed,int j)
{
    std::mt19937 gen(seed);
    std::vector<double> r(2*N);
    double A=0.0;
    auto start=std::chrono::steady_clock::now();
    
    //inicialización de las partículas
    I_state(r,lattice,Iseed);
    
    //evolución del sistema en n pasos de camino aleatorio
    for(int i=0;i<n;i++){
        n_state(r,lattice,gen);
        A=E(r,lattice,j);
    }
    auto end=std::chrono::steady_clock::now();
    A+=0;
    double t=std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    std::cout<<N<<"\t"<<t<<"\n";//std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count()<<"\n";
}
