#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<cmath>

struct particle{
    double mass;
    double rad;
    std::vector<double> r;
    std::vector<double> v;
    std::vector<double> F;
};

void print(std::vector<particle> &p,double t);
void p_print(std::vector<particle> &p,int istep);
void initial_conditions(std::vector<particle> &p,double Temp,double R);
void set_F(std::vector<particle> &p);
void start(std::vector<particle> &p,double dt);
void leap_frog(std::vector<particle> &p,double dt);

const double g=9.81; //gravedad terrestre
const double dt=0.01; //paso de tiempo de evolución
const int Nsteps=1000; //número de pasos
const double K=500.0; //constante de los resortes que modelan las paredes
const int N=2; //número de partículas
const double R=8.314472; //constante universal de los gases en J/K*mol
const double Temp=293.15; //temperatura en kelvin (20°)

int main(int argc, char **argv)
{
    std::vector<particle> p(N);

    initial_conditions(p,Temp,R);
    set_F(p);
    start(p,dt);
    
    //si quiero imprimir a pantalla para gnuplot
    //print(p,0.0);
    

    //si quiero animar en paraview
    p_print(p,0);

    for(int i=1;i<=Nsteps;i++){
        leap_frog(p,dt);
        set_F(p);
        
        //si quiero imprimir a pantalla para gnuplot
        //print(p,i*dt);

        //si quiero animar en paraview
        p_print(p,i);
    }
    
    
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
        fout<<p[n].rad<<" ";
        for(int i=0;i<3;i++){
            fout<<p[n].r[i]<<" ";
        }
        fout<<"\n";
    }
}

void initial_conditions(std::vector<particle> &p,double Temp,double R)
{
    for(long unsigned int i=0;i<p.size();i++){
        p[i].r.resize(3);
        p[i].v.resize(3);
        p[i].F.resize(3);
        p[i].mass=1.0;
        p[i].rad=1.0;
    }

    //inicialización aleatoria de las partículas siguiendo la equipartición de la energía
    std::mt19937 gen(0);
    std::uniform_real_distribution<> dis(-1,1);
    std::uniform_real_distribution<> h(0,30);
    std::uniform_real_distribution<> x(0,10);

    for(long unsigned int n=0;n<p.size();n++){
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
        double vrms=std::sqrt((3*R*Temp)/p[n].mass);
        double v=std::hypot(p[n].v[0],p[n].v[1],p[n].v[2]);

        for(int i=0;i<3;i++){
            p[n].v[i]*=vrms/v;
        }
    }
}

void set_F(std::vector<particle> &p)
{
    //reset
    for(long unsigned int n=0;n<p.size();n++){
        for(int i=0;i<3;i++){
            p[n].F[i]=0.0;
        }
    }
    
    //gravity
    for(long unsigned int n=0;n<p.size();n++){
        p[n].F[2]-=p[n].mass*g;
    }

    //bounce by other particles
    double d=std::hypot(p[0].r[0]-p[1].r[0],p[0].r[1]-p[1].r[1],p[0].r[2]-p[1].r[2]);
    double h=p[0].rad+p[1].rad-d;
    if(h>0){
        for(int i=0;i<3;i++){
            p[0].F[i]=(K*h*(p[0].r[i]-p[1].r[i]))/d;
            p[1].F[i]=-p[0].F[i];
        }
    }

    //ground
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad-p[n].r[2];
        if(delta>0){
            p[n].F[2]+=K*delta;
            p[n].F[2]-=0.5*p[n].v[2];
        }
    }

    //roof
    double Lz=30.0;
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad+p[n].r[2]-Lz;
        if(delta>0){
            p[n].F[2]-=K*delta;
            p[n].F[2]-=0.5*p[n].v[2];
        }
    }

    //left wall
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad-p[n].r[1];
        if(delta>0){
            p[n].F[1]+=K*delta;
            p[n].F[1]-=0.5*p[n].v[1];
        }
    }

    //right wall
    double Ly=10.0;
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad+p[n].r[1]-Ly;
        if(delta>0){
            p[n].F[1]-=K*delta;
            p[n].F[1]-=0.5*p[n].v[1];
        }
    }

    //back wall
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad-p[n].r[0];
        if(delta>0){
            p[n].F[0]+=K*delta;
            p[n].F[0]-=0.5*p[n].v[0];
        }
    }

    //front wall
    double Lx=10.0;
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad+p[n].r[0]-Lx;
        if(delta>0){
            p[n].F[0]-=K*delta;
            p[n].F[0]-=0.5*p[n].v[0];
        }
    }
}

void start(std::vector<particle> &p,double dt)
{
    for(long unsigned int n=0;n<p.size();n++){
        for(int i=0;i<3;i++){
            p[n].v[i]-=p[n].F[i]*dt/(2*p[n].mass);
        }
    }
}

void leap_frog(std::vector<particle> &p,double dt)
{
    for(long unsigned int n=0;n<p.size();n++){
        for(int i=0;i<3;i++){
            p[n].v[i]+=p[n].F[i]*dt/(p[n].mass);
        }
        for(int i=0;i<3;i++){
            p[n].r[i]+=p[n].v[i]*dt;
        }
    }
}
