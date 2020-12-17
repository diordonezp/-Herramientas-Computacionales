#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<cmath>
#include"omp.h"

struct particle{
    double mass;
    double rad;
    std::vector<double> r;
    std::vector<double> v;
    std::vector<double> F;
};

void print(std::vector<particle> &p,double t);
void p_print(std::vector<particle> &p,int istep);
void initial_conditions(std::vector<particle> &p,double Temp,double R,int thr_N);
void set_F(std::vector<particle> &p,int thr_N);
void start(std::vector<particle> &p,double dt,int thr_N);
void leap_frog(std::vector<particle> &p,double dt,int thr_N);
double density(std::vector<particle> &p, double h, double tin);
int dist_prob(std::vector<particle> &p,double vel,double h);

const double g=9.81; //gravedad terrestre
const double dt=0.05; //paso de tiempo de evolución
const int Nsteps=1000; //número de pasos
const double K=250.0; //constante de los resortes que modelan las paredes
const int N=1000; //número de partículas
const double k_b=1.380649e-23; //constante de Boltzmann
const double Temp=500; //temperatura en kelvin

int main(int argc, char **argv)
{
    int num_threads=std::atoi(argv[1]);
    
    std::vector<particle> p(N);

    initial_conditions(p,Temp,k_b,num_threads);
    set_F(p,num_threads);
    start(p,dt,num_threads);
    
    //si quiero imprimir a pantalla para gnuplot
    //print(p,0.0);
    

    //si quiero animar en paraview
    p_print(p,0);

    for(int i=1;i<=Nsteps;i++){
        std::cout<<i<<"\n";
        leap_frog(p,dt,num_threads);
        set_F(p,num_threads);
        
        //si quiero imprimir a pantalla para gnuplot
        //print(p,i*dt);

        //si quiero animar en paraview
        p_print(p,i);
    }
    
    /*for(double h=0.0;h<=30;h+=0.1){
        std::cout<<h<<" "<<density(p,h,0.1)<<"\n";
    }

    for(double v=0.0;v<=100;v+=0.5){
        std::cout<<v<<" "<<dist_prob(p,v,0.2)<<"\n";
    }*/
    
    return 0;
}

void print(std::vector<particle> &p,double t)
{
    std::cout<<t<<" ";
    for(long unsigned int n=0;n<p.size();n++){
        std::cout<<p[n].rad<<" ";
        for(int i=0;i<3;i++){
            std::cout<<p[n].r[i]<<" ";
        }
        for(int i=0;i<3;i++){
            std::cout<<p[n].v[i]<<" ";
        }
    }
    std::cout<<"\n";
}

void p_print(std::vector<particle> &p,int istep)
{
    std::string fname="post/datos-"+std::to_string(istep)+".csv";
    std::ofstream fout(fname);
    
    for(long unsigned int n=0;n<p.size();n++){
        fout<<p[n].rad<<", ";
        for(int i=0;i<3;i++){
            fout<<p[n].r[i]<<", ";
        }
        fout<<"\n";
    }
}

void initial_conditions(std::vector<particle> &p,double Temp,double R,int thr_N)
{

    //inicialización aleatoria de las partículas siguiendo la equipartición de la energía
    std::mt19937 gen(19937);
    std::uniform_real_distribution<> dis(-1,1);
    std::uniform_real_distribution<> h(0,30);
    std::uniform_real_distribution<> x(0,10);

#pragma omp parallel for num_threads(thr_N)
    for(long unsigned int n=0;n<p.size();n++){
        p[n].r.resize(3);
        p[n].v.resize(3);
        p[n].F.resize(3);
        p[n].mass=1.0;
        p[n].rad=0.1;
        
        for(int i=0;i<3;i++)
        {
            p[n].F[i]=0.0;
            p[n].v[i]=dis(gen);
            if(i==2){
                p[n].r[i]=h(gen);
            }
            else{
                p[n].r[i]=x(gen);
            }
        }
        double vrms=std::sqrt((3*k_b*Temp)/p[n].mass);
        double v=std::hypot(p[n].v[0],p[n].v[1],p[n].v[2]);
        
        for(int i=0;i<3;i++){
            p[n].v[i]*=vrms/v;
        }
    }   
}

void set_F(std::vector<particle> &p,int thr_N)
{
    double Lx=10.0;
    double Ly=10.0;
    double Lz=30.0;

#pragma omp parallel for num_threads(thr_N)
    for(long unsigned int n=0;n<p.size();n++){

        //reset
        for(int i=0;i<3;i++){
            p[n].F[i]=0.0;
        }
        
        //gravity
        p[n].F[2]-=p[n].mass*g;

        //bounce by other particles
        for(long unsigned int m=n+1;m<p.size();m++){
            double d=std::hypot(p[n].r[0]-p[m].r[0],p[n].r[1]-p[m].r[1],p[n].r[2]-p[m].r[2]);
            double h=p[n].rad+p[m].rad-d;
            if(h>0){
                for(int i=0;i<3;i++){
                    p[n].F[i]=(K*h*(p[n].r[i]-p[m].r[i]))/d;
                    p[m].F[i]=-p[n].F[i];
                }
            }
        }
        
        //ground
        if(p[n].rad-p[n].r[2]>0){
            p[n].F[2]+=K*(p[n].rad-p[n].r[2]);
            p[n].F[2]-=0.5*p[n].v[2];
        }
        
        //roof
        if(p[n].rad+p[n].r[2]-Lz>0){
            p[n].F[2]-=K*(p[n].rad+p[n].r[2]-Lz);
            p[n].F[2]-=0.5*p[n].v[2];
        }
        
        //left wall
        if(p[n].rad-p[n].r[1]>0){
            p[n].F[1]+=K*(p[n].rad-p[n].r[1]);
            p[n].F[1]-=0.5*p[n].v[1];
        }
        
        //right wall
        if(p[n].rad+p[n].r[1]-Ly>0){
            p[n].F[1]-=K*(p[n].rad+p[n].r[1]-Ly);
            p[n].F[1]-=0.5*p[n].v[1];
        }
        
        //back wall
        if(p[n].rad-p[n].r[0]>0){
            p[n].F[0]+=K*(p[n].rad-p[n].r[0]);
            p[n].F[0]-=0.5*p[n].v[0];
        }
        
        //front wall
        if(p[n].rad+p[n].r[0]-Lx>0){
            p[n].F[0]-=K*(p[n].rad+p[n].r[0]-Lx);
            p[n].F[0]-=0.5*p[n].v[0];
        }
    }
}

void start(std::vector<particle> &p,double dt,int thr_N)
{
#pragma omp parallel for num_threads(thr_N)
    for(long unsigned int n=0;n<p.size();n++){
        for(int i=0;i<3;i++){
            p[n].v[i]-=p[n].F[i]*dt/(2*p[n].mass);
        }
    }
}

void leap_frog(std::vector<particle> &p,double dt,int thr_N)
{
#pragma omp parallel for num_threads(thr_N)
    for(long unsigned int n=0;n<p.size();n++){
        for(int i=0;i<3;i++){
            p[n].v[i]+=p[n].F[i]*dt/(p[n].mass);
        }
        for(int i=0;i<3;i++){
            p[n].r[i]+=p[n].v[i]*dt;
        }
    }
}

double density(std::vector<particle> &p, double h, double tin)
{
    int sum=0;

    for(long unsigned int n=0;n<p.size();n++){
        if(p[n].r[2]<0){
            p[n].r[2]=0;
        }
    }

    for(long unsigned int n=0;n<p.size();n++){
        if(p[n].r[2]<=h+tin && p[n].r[2]>=h-tin){
            sum+=1;
        }
    }

    return sum;
}

int dist_prob(std::vector<particle> &p,double vel,double h)
{
    int count=0;
    
    for(long unsigned int n=0;n<p.size();n++){
        double v=std::hypot(p[n].v[0],p[n].v[1],p[n].v[2]);
        if(v>vel-h && v<vel+h){
            count+=1;
        }
    }

    return count;
}
