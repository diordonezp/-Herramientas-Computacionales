#include<iostream>
#include<vector>
#include<random>

class particle{
    private:
        double mass;
        double rad;
        std::vector<double> r;
        std::vector<double> v;
        std::vector<double> F;
    public:
        particle();
        particle(double Temp,double k_b,int seed);
        void s_print(double t);
        void set_F();
        void start();
        void leap_frog(double dt);
};

const double g=9.81; //gravedad terrestre
const double dt=0.05; //paso de tiempo de evolución
const int Nsteps=1000; //número de pasos
const double K=250.0; //constante de los resortes que modelan las paredes
const int N=5000; //número de partículas
const double k_b=1.380649e-23; //constante de Boltzmann
const double Temp=500; //temperatura en kelvin

int main(void)
{
    particle body;

    body=particle(0,0,0);
    body.set_F();
    body.s_print(0);

    return 0;
}

particle::particle()
{
    //nada
}

particle::particle(double Temp,double k_b,int seed)
{
    mass=1.0;
    rad=1.0;
    r.resize(3);
    v.resize(3);
    F.resize(3);
    for(int i=0;i<3;i++){
        r[i]=0;
        v[i]=0;
        F[i]=0;
    }
}

void particle::s_print(double t)
{
    std::cout<<t<<" "<<mass<<" "<<rad;
    for(int i=0;i<3;i++){
        std::cout<<" "<<r[i];
    }
    for(int i=0;i<3;i++){
        std::cout<<" "<<v[i];
    }
    for(int i=0;i<3;i++){
        std::cout<<" "<<F[i];
    }
    
    std::cout<<"\n";
}

void particle::set_F()
{
    //reset
    for(int i=0;i<3;i++){
        F[i]=0.0;
    }
    
    //gravity
    F[2]-=mass*g;

    /*//bounce by other particles
    for(long unsigned int n=0;n<p.size();n++){
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
        }*/

    //box:
    double Lz=30.0;
    double Ly=10.0;
    double Lx=10.0;
    
    //ground
    if(rad-r[2]>0){
        F[2]+=K*(rad-r[2]);
        F[2]-=0.5*v[2];
    }

    //roof
    if(rad+r[2]-Lz>0){
        F[2]-=K*(rad+r[2]-Lz);
        F[2]-=0.5*v[2];
    }
    
    //left wall
    if(rad-r[1]>0){
        F[1]+=K*(rad-r[1]);
        F[1]-=0.5*v[1];
    }
    
    //right wall
    if(rad+r[1]-Ly>0){
        F[1]-=K*(rad+r[1]-Ly);
        F[1]-=0.5*v[1];
    }

    //back wall
    if(rad-r[0]>0){
        F[0]+=K*(rad-r[0]);
        F[0]-=0.5*v[0];
    }

    //front wall
    if(rad+r[0]-Lx>0){
        F[0]-=K*(rad+r[0]-Lx);
        F[0]-=0.5*v[0];
    }
}
