#include<iostream>
#include<vector>
#include<random>
#include"main.hpp"

int main(void)
{
    double lattice=100.0;//mitad de la longitud de la caja que encierra
    //las partículas
    int N=400;//número de partículas
    int n=1e5;//iteraciones
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
