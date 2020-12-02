#include <iostream>
#include <numeric>
#include <cstdlib>
#include "mpi.h"

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  const int NPINGPONG = std::atoi(argv[1]);
  int pid = 0, nproc = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  int ball=10;

  for(int i=0;i<NPINGPONG;i++){
    if(pid==0){
      MPI_Send(&ball,1,MPI_INT,1,0,MPI_COMM_WORLD);
      MPI_Recv(&ball,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    
    if(pid==1){
      MPI_Recv(&ball,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      ball+=1;
      MPI_Send(&ball,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
  }

  if(pid==0){
    std::cout<<ball<<"\n";
  }
  
  MPI_Finalize();
  return 0;
}
