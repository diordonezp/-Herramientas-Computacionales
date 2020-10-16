#pragma once

void print(std::vector<double> r);
void I_state(std::vector<double> &r,double l,int Iseed);
void n_state(std::vector<double> &r,double l,std::mt19937 &gen);
double E(std::vector<double> r,double l,int m);
