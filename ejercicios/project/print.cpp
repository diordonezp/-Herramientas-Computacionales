#include<vector>
#include<iostream>

void print(std::vector<double> r)
{
    for(long unsigned int i=0;i<r.size();i+=2){
        std::cout<<r[i]<<"\t"<<r[i+1]<<"\n";
    }
}
