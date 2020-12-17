// Pingpong: pid 0 sends a counter to pid 1. Pid 1 increments it, and sends it back. pid 0 prints it
// NPINGPONG: Number of ping pong interchange

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

  int counter = 0;
  int tag = 0;
  //  for (int istep = 0; istep < NPINGPONG; ++istep) {
  while(counter < NPINGPONG) {
    if (0 == pid) {
      std::cout << "Pid 0 sends " << counter << " to pid 1 " << std::endl;
      MPI_Send(&counter, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
      MPI_Recv(&counter, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      std::cout << "Pid 0 receives " << counter << " from pid 1 " << std::endl;
    } else {
      std::cout << "Pid 1 receives " << counter << " from pid 0 " << std::endl;
      MPI_Recv(&counter, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      counter++;
      std::cout << "Pid 1 sends " << counter << " to pid 0 " << std::endl;
      MPI_Send(&counter, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
  }

  if (0 == pid) {
    std::cout << counter << std::endl;
  }
  
  MPI_Finalize();
  return 0;
}

