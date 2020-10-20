#include<iostream>
#include<fstream>
#include<vector>
#include<random>
#include"main.hpp"

int main(void)
{
    std::cout.precision(15);std::cout.setf(std::ios::scientific);
    std::ifstream fin("instructions/Parameters.txt");

    int N=0;;//número de partículas
    fin>>N;
    double lattice=0.0;//mitad de la longitud de la caja que encierra
    //las partículas
    fin>>lattice;
    int n=0;//iteraciones
    fin>>n;
    int seed=0;//semilla aleatoria para evolución del sistema
    fin>>seed;
    int Iseed=0;//semilla aleatoria para el estado inicial
    int j=8;//número de casillas por lado de la grilla -> grilla jxj

    std::mt19937 gen(seed);
    
    std::vector<double> r(2*N);
    
    //inicialización de las partículas
    I_state(r,lattice,Iseed);
    
    //evolución del sistema en n pasos de camino aleatorio
    for(int i=0;i<n;i++){
        n_state(r,lattice,gen);
        std::cout<<i<<"\t"<<E(r,lattice,j)<<"\n";
    }
    
    fin.close();
    return 0;
}
