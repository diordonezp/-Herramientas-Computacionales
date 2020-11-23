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

int main(int argc, char **argv)
{
    std::vector<particle> p(1);

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
    std::cout<<p[0].mass<<" "<<p[0].rad<<" "<<t<<" ";
    for(int i=0;i<3;i++){
        std::cout<<p[0].r[i]<<" ";
    }
    std::cout<<p[0].F[0]<<"\n";
}

void initial_conditions(std::vector<particle> &p)
{
    p[0].r.resize(3);
    p[0].v.resize(3);
    p[0].F.resize(3);
    p[0].mass=5.0;
    p[0].rad=1.0;

    for(int i=0;i<3;i++)
    {
        p[0].r[i]=0.0;
    }

    p[0].r[0]=5;
}

void set_F(std::vector<particle> &p)
{
    //reset
    for(int i=0;i<3;i++){
        p[0].F[i]=0.0;
    }
    
    //gravity
    //p[0].F[2]-=p[0].mass*g;

    p[0].F[0]-=p[0].r[0];
}

void start(std::vector<particle> &p,double dt)
{
    for(int i=0;i<3;i++){
        p[0].v[i]-=p[0].F[i]*dt/(2*p[0].mass);
    }
}

void leap_frog(std::vector<particle> &p,double dt)
{
    for(int i=0;i<3;i++){
        p[0].v[i]+=p[0].F[i]*dt/(p[0].mass);
    }
    for(int i=0;i<3;i++){
        p[0].r[i]+=p[0].v[i]*dt;
    }
}
