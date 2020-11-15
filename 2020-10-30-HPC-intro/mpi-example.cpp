#include<iostream>
#include<mpi.h>

int main(int argc,char**argv)
{
    MPI_Init(&argc,&argv);
    
    int rank,size;//rank: who am i?, size: of how many?

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    std::cout<<"hello from process: "<<rank<<" out of "<<size<<"\n";
    
    MPI_Finalize(); 

    return 0;
}
