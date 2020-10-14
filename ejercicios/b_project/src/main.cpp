#include"atom.hpp"


//double entropy()

int main(void)
{
    double lattice=100;//mitad de la longitud de la caja que encierra
    //las partículas
    int N=400;//número de partículas
    int n=1e4;//iteraciones
    int seed=0;//semilla aleatoria para evolución del sistema
    int Iseed=0;//semilla aleatoria para el estado inicial

    std::mt19937 gen(seed);
    std::mt19937 Igen(Iseed);
    
    atom atoms[N];

    for(auto &particle:atoms){
        particle=atom(lattice,Igen);
    }

    for(int i=0;i<n;i++){
        for(auto &particle:atoms){
            particle.n_state(lattice,gen);//a cada atomo de la clase, estoy accediendo a la rutina n_state.
        }
    }

    for(auto particle:atoms){
        std::cout<<particle<<"\n";
    }
    
    return 0;
}

