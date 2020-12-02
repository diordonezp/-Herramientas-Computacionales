#include <iostream>
#include <numeric>
#include <cstdlib>
#include "mpi.h"

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int pid = 0, nproc = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  int ball=0;

  if(pid==0){
      MPI_Send(&ball,1,MPI_INT,1,0,MPI_COMM_WORLD);
      MPI_Recv(&ball,1,MPI_INT,nproc-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      std::cout<<ball<<"\n";
  }
  
  if(pid>0 && pid<nproc-1){
      MPI_Recv(&ball,1,MPI_INT,pid-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      ball+=pid;
      MPI_Send(&ball,1,MPI_INT,pid+1,0,MPI_COMM_WORLD);
  }
  if(pid==nproc-1){
      MPI_Recv(&ball,1,MPI_INT,pid-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      ball+=pid;
      MPI_Send(&ball,1,MPI_INT,0,0,MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
  return 0;
}
