#include <iostream>
#include "mpi.h"

const int NS = 100;

void fill(double *data, int ns, int nslocal, int pid, int nproc);
void print(double *data, int ns, int nslocal, int pid, int nproc);
void print_local(double *data, int ns, int nslocal, int pid, int nproc);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int pid = 0, nproc = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  const int NSlocal = NS/nproc;
  double * data = new double [NSlocal] {0.0};
  
  fill(data, NS, NSlocal, pid, nproc);
  // parallel print
  print(data, NS, NSlocal, pid, nproc);
  
  delete [] data;
  MPI_Finalize();
  return 0;
}

void fill(double *data, int ns, int nslocal, int pid, int nproc)
{
  for (int ilocal = 0; ilocal < nslocal; ++ilocal) {
    data[ilocal] = 2*(pid*nslocal + ilocal);
  }
}

void print(double *data, int ns, int nslocal, int pid, int nproc)
{
 int tag = 0;
  if (0 == pid) {
    double * aux = new double [nslocal] {0.0};
    print_local(data, ns, nslocal, pid, nproc);
    for (int src = 1; src < nproc; ++src) {
      MPI_Recv(aux, nslocal, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      print_local(aux, ns, nslocal, src, nproc);
    }
    delete [] aux;
  } else {
    int dest = 0;
    MPI_Send(data, nslocal, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
}

void print_local(double *data, int ns, int nslocal, int pid, int nproc)
{
  std::cout << "pid: " << pid << "\n";
  for (int ilocal = 0; ilocal < nslocal; ++ilocal) {
    std::cout << data[ilocal] << "  ";
  }
  std::cout << "\n";
}
