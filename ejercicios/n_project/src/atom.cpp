#include "atom.hpp"

std::ostream &operator<<(std::ostream &os,const atom &at)
{
    os<<at.x<<"\t"<<at.y;

    return os;
}

atom::atom()
{

}

atom::atom(double l,std::mt19937 &gen)
{
    std::uniform_real_distribution<> dis(-l/10,l/10);

    x=dis(gen);
    y=dis(gen);
}

void atom::n_state(double l,std::mt19937 &gen)
{
    double dl=0.05;
    std::uniform_real_distribution<> dis(-dl,dl);
    double dx=dis(gen);
    double dy=dis(gen);

    if(std::hypot(dx,dy)>dl){
        dx*=dl/std::hypot(dx,dy);
        dy*=dl/std::hypot(dx,dy);
    }
    x+=dx;
    y+=dy;
    if(x>l){
        x=l;
    }
    if(x<-l){
        x=-l;
    }
    if(y>l){
        y=l;
    }
    if(y<-l){
        y=-l;
    }
}
