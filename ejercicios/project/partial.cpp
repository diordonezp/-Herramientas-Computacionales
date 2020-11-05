#include<iostream>
#include<vector>
#include<random>

void print(std::vector<double> r);
void I_state(std::vector<double> &r,double l, int Iseed);
void n_state(std::vector<double> &r,double l,std::mt19937 &gen);

int main(void)
{
    std::cout.precision(15);std::cout.setf(std::ios::scientific);

    int N=400;//número de partículas
    double lattice=50.0;//mitad de la longitud de la caja que encierra las partículas
    int n=1e7;//iteraciones
    int seed=19337;//semilla aleatoria para evolución del sistema
    int Iseed=0;//semilla aleatoria para el estado inicial

    std::mt19937 gen(seed);
    
    std::vector<double> r(2*N);
    
    //inicialización de las partículas
    I_state(r,lattice,Iseed);
    
    //evolución del sistema en n pasos de camino aleatorio
    for(int i=0;i<n;i++){
        n_state(r,lattice,gen);
        if(i%1000==0){
            std::cout<<i<<"\t"<<r.size()/2<<"\n";
        }
    }
    
    return 0;
}

void print(std::vector<double> r)
{
    for(long unsigned int i=0;i<r.size();i+=2){
        std::cout<<r[i]<<"\t"<<r[i+1]<<"\n";
    }
}

void I_state(std::vector<double> &r,double l, int Iseed)
{
    std::mt19937 gen(Iseed);
    std::uniform_real_distribution<> dis(-l/10,l/10);
    
    /*se le asigna a cada elemento un valor aleatorio dentro de una caja
      de dimensión l/5*l/5*/
    for(long unsigned int i=0;i<r.size();i++){
        r[i]=dis(gen);
    }
}

void n_state(std::vector<double> &r,double l,std::mt19937 &gen)
{
    double dl=0.15;
    std::uniform_real_distribution<> dis(-dl,dl);
    
    /*a cada elemento del vector, se suma una cantidad aleatoria pequeña
      y se verifica que el nuevo elemento no se salga de las paredes, en
      tal caso, se le devuelve a la pared*/
    for(long unsigned int i=0;i<r.size();i+=2){
        r[i]+=dis(gen);
        r[i+1]+=dis(gen);

        if(r[i+1]<-40 && r[i]>l){
            r.erase(r.begin()+i,r.begin()+i+2);
        }
        
        if(r[i]>l){
            r[i]=l;
        }
        if(r[i]<-l){
            r[i]=-l;
        }
        if(r[i+1]>l){
            r[i+1]=l;
        }
        if(r[i+1]<-l){
            r[i+1]=-l;
        } 
    }
}
