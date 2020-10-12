#include<iostream>
#include<vector>
#include<random>

void print(std::vector<double> r);
void n_state(std::vector<double> &r,int n,int seed);

int main(void)
{
    double lattice=20;
    int N=5;
    int seed=0;
    
    std::vector<double> r(2*N*N);
    
    for(int i=0;i<2*N;i+=2){
        for(int j=0;j<2*N;j+=2){
            r[i*N+j]=(-(N-1)/2)+i/2;
            r[i*N+j+1]=((N-1)/2)-j/2;
        }
    }

    print(r);
    
    return 0;
}

void print(std::vector<double> r)
{
    for(int i=0;i<r.size();i+=2){
        std::cout<<r[i]<<"\t"<<r[i+1]<<"\n";
    }
}

void n_state(std::vector<double> &r,int n,int seed)
{
    double dl=0.1;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-dl,dl);
    
    for(int j=0;j<n;j++){
        for(int i=0;i<r.size();i++){
            r[i]+=dis(gen);
        }
    }
}
