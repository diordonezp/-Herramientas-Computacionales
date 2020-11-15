#include<iostream>
#include<omp.h>

int main(int argc, char**argv)
{
#pragma omp parallel
    {
        int tid=omp_get_thread_num();
        int nth=omp_get_num_threads();
        
        for(int i=0;i<nth;i++){
            if(tid==i){
                std::cout<<"tid: "<<tid<<"\n";
            }
        }
    }

    return 0;
}
