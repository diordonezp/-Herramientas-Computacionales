#ifndef __ATOM_H_
#define __ATOM_H_
#include<iostream>
#include<random>
#include<cmath>

class atom{
    private:
        double x;
        double y;
    public:
        atom();//es obligado un construtor por defecto
        atom(double l,std::mt19937 &gen);//constructor: mismo nombre que la clase
        void n_state(double l,std::mt19937 &gen);
        friend std::ostream &operator<<(std::ostream &os,const atom &at);
};

#endif // __ATOM_H_
