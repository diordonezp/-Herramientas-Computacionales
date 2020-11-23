#include<iostream>
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
void initial_conditions(std::vector<particle> &p);
void set_F(std::vector<particle> &p);
void start(std::vector<particle> &p,double dt);
void leap_frog(std::vector<particle> &p,double dt);

const double g=9.81;
const double dt=0.01;
const int N=1000;
const double K=250.0;

int main(int argc, char **argv)
{
    std::vector<particle> p(2);

    initial_conditions(p);
    set_F(p);
    start(p,dt);
    print(p,0.0);

    for(int i=0;i<N;i++){
        leap_frog(p,dt);
        set_F(p);
        print(p,i*dt);
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
        std::cout<<" ";
    }
    std::cout<<"\n";
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

    p[0].r[2]=5.0;
    p[1].r[0]=0.0;
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

    //ground
    for(long unsigned int n=0;n<p.size();n++){
        double delta=p[n].rad-p[n].r[2];
        if(delta>0){
            p[n].F[2]+=K*delta;
            p[n].F[2]-=0.5*p[n].v[2];
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
