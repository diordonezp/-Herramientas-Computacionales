#include<iostream>
#include<vector>
#include<random>

void print(std::vector<double> r);
void I_state(std::vector<double> &r,double l,int Iseed);
void n_state(std::vector<double> &r,int n,int seed);

int main(void)
{
    double lattice=100;//longitud de la caja que encierra las partículas
    int N=400;//número de partículas
    int n=1e6;//iteraciones
    int seed=0;//semilla aleatoria para evolución del sistema
    int Iseed=0;//semilla aleatoria para el estado inicial
    
    std::vector<double> r(2*N);
    
    /*for(int i=0;i<2*N;i+=2){
        for(int j=0;j<2*N;j+=2){
            r[i*N+j]=(-(N-1)/2)+i/2;
            r[i*N+j+1]=((N-1)/2)-j/2;
        }
        }*/
    I_state(r,lattice,Iseed);
    n_state(r,n,seed);
    print(r);
    
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
    //std::random_device vd;
    std::mt19937 gen(Iseed);
    std::uniform_real_distribution<> dis(-l/20,l/20);

    for(int i=0;i<r.size();i++){
        r[i]=dis(gen);
    }
}

void n_state(std::vector<double> &r,int n,int seed)
{
    double dl=0.01;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-dl,dl);
    
    for(int j=0;j<n;j++){
        for(int i=0;i<r.size();i++){
            r[i]+=dis(gen);
        }
    }
}
