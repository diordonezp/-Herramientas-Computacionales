#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>

struct particle{
    double mass;
    double rad;
    std::vector<double> r;
    std::vector<double> v;
    std::vector<double> F;
};

void print(std::vector<particle> &p,double t);
void p_print(std::vector<particle> &p,int istep);
void initial_conditions(std::vector<particle> &p);
void set_F(std::vector<particle> &p);
void start(std::vector<particle> &p,double dt);
void leap_frog(std::vector<particle> &p,double dt);

const double g=9.81;
const double dt=0.05;
const int Nsteps=1000;
const double K=250.0;
const int N=2;

int main(int argc, char **argv)
{
    std::vector<particle> p(N);

    initial_conditions(p);
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

void initial_conditions(std::vector<particle> &p)
{
    for(long unsigned int i=0;i<p.size();i++){
        p[i].r.resize(3);
        p[i].v.resize(3);
        p[i].F.resize(3);
        p[i].mass=1.0;
        p[i].rad=1.0;
    }

    for(long unsigned int n=0;n<p.size();n++){
        for(int i=0;i<3;i++)
        {
            p[n].r[i]=0.0;
            p[n].v[i]=0.0;
            p[n].F[i]=0.0;
        }
    }

    p[0].r[0]=5.0;
    p[0].r[1]=5.0;
    p[0].r[2]=25.0;
    p[0].v[0]=0.2;
    p[0].v[1]=1.0;
    p[0].v[2]=15.0;
    
    p[1].r[0]=0.0;
    p[1].r[1]=0.0;
    p[1].r[2]=10.0;
    p[1].v[0]=0.0;
    p[1].v[1]=1.0;
    p[1].v[2]=1.0;
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
