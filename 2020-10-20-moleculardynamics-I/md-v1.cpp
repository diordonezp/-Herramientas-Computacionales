#include<iostream>
#include<fstream>
#include<vector>

struct body{
    double masa;
    double r[3],v[3],F[3];
};

//simulation conditions
const int N=1;
const double g=9.81;
const double Dt=0.1;

//helper functions
void initial_conditions(std::vector<body> &bodies);
void timestep(std::vector<body> &bodies,double dt);
void start_timeintegration(std::vector<body> &bodies,double dt);
void compute_force(std::vector<body> &bodies);
void print_system(const std::vector<body> &bodies,double time);

int main(void)
{
    std::vector<body> bodies(N);

    initial_conditions(bodies);
    compute_force(bodies);
    print_system(bodies,0);
    start_timerintegration(bodies,DT);
    print_system(bodies,0);   
    return 0;
}

void initial_conditions(std::vector<body> &bodies)
{
    bodies[0].masa=1.23;
    bodies[0].r[2]=7.86;
    bodies[0].v[2]=1.32;
}

void timestep(std::vector<body> &bodies,double dt)
{
}

void start_timeintegration(std::vector<body> &bodies,double dt)
{
    for(auto &cuerpo:bodies){
        cuerpo.v[0]=cuerpo.v[0]-dt*cuerpo.F[0]/(2*cuerpo.masa);
        cuerpo.v[1]=cuerpo.v[1]-dt*cuerpo.F[1]/(2*cuerpo.masa);
        cuerpo.v[2]=cuerpo.v[2]-dt*cuerpo.F[2]/(2*cuerpo.masa);
    }
}

void compute_force(std::vector<body> &bodies)
{
    //reset forces
     for(auto &cuerpo:bodies){
        cuerpo.F[0]=cuerpo.F[1]=cuerpo.F[2]=0.0;
    }

     //gravity
    for(auto &cuerpo:bodies){
        cuerpo.F[2]-=cuerpo.masa*g;
    }
}

void print_system(const std::vector<body> &bodies,double time)
{
    std::ofstream fout("datos.txt");
    fout.precision(15); fout.setf(std::ios::scientific);
    
    for(const auto &cuerpo:bodies){
        fout<<cuerpo.r[0]<<"  "<<cuerpo.r[1]<<"  "<<cuerpo.r[2]<<"  "
            <<cuerpo.v[0]<<"  "<<cuerpo.v[1]<<"  "<<cuerpo.v[2]<<"  "
            <<cuerpo.F[0]<<"  "<<cuerpo.F[1]<<"  "<<cuerpo.F[2]<<"  "
            <<cuerpo.masa<<"\n";
    }
    fout.close();
}
