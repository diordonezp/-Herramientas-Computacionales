#include <iostream>
#include <vector>
#include <mpi.h>

const double DELTA = 0.1;
const double XMIN = 0.0;
const double XMAX = 1.0;
const double YMIN = 0.0;
const double YMAX = 1.2;
const int NX = (XMAX-XMIN)/DELTA;
const int NY = (YMAX-YMIN)/DELTA;
const int NSTEPS = 0;

typedef std::vector<double> data_t;

// parallel functions
void initial_conditions(data_t & data, int nx, int ny, int pid, int np);
void print_screen(const data_t & data, int nx, int ny, int pid, int nproc);

// serial functions
void initial_conditions(data_t & data, int nx, int ny);
void boundary_conditions(data_t & data, int nx, int ny);
void evolve(data_t & data, int nx, int ny, int nsteps);
void relaxation_step(data_t & data, int nx, int ny);
void print_screen(const data_t & data, int nx, int ny);
void start_gnuplot(void);
void print_gnuplot(const data_t & data, int nx, int ny);


int main(int argc, char **argv)
{
    int pid = 0, nproc = 0;
    // init mpi environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    // declare data structures
    int NXlocal = NX/nproc; // TODO: Faltan los ghosts
    data_t potential(NXlocal*NY); // [ii, jj] -> ii*NY + jj

    // set initial and boundary conditions
    initial_conditions(potential, NXlocal, NY, pid, nproc);
    print_screen(potential, NXlocal, NY, pid, nproc);
    //boundary_conditions(potential, NX, NY);

    // evolve and print
    //evolve(potential, NX, NY, NSTEPS);

    // close mpi environment
    MPI_Finalize();

    return 0;
}

void initial_conditions(data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = 1.0;
        }
    }
}
void initial_conditions(data_t & data, int nx, int ny, int pid, int np)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            data[ix*ny + iy] = pid;
        }
    }
}

void boundary_conditions(data_t & data, int nx, int ny)
{
    int ix, iy;
    // first row
    ix = 0;
    for(int iy = 0; iy < ny; ++iy) {
        data[ix*ny + iy] = 100.0;
    }
    // last row
    ix = nx-1;
    for(int iy = 0; iy < ny; ++iy) {
        data[ix*ny + iy] = 0.0;
    }
    // first column
    iy = 0;
    for(int ix = 1; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
    // last column
    iy = ny-1;
    for(int ix = 1; ix < nx; ++ix) {
        data[ix*ny + iy] = 0.0;
    }
    //new
    //ix = nx/2;
    //for(int iy = ny/3; iy <= 2*ny/3; ++iy) {
    //    data[ix*ny + iy] = -50.0;
    //}
}

void evolve(data_t & data, int nx, int ny, int nsteps)
{
    //start_gnuplot();
    print_screen(data, nx, ny);
    for(int istep = 0; istep < nsteps; ++istep) {
        relaxation_step(data, nx, ny);
        print_screen(data, nx, ny);
        //print_gnuplot(data, nx, ny);
    }
}
void relaxation_step(data_t & data, int nx, int ny)
{
    // recorrer toda la matriz y aplicar el algoritmo,
    // teniendo cuidado con no modificar las condiciones de
    // frontera
    for(int ix = 1; ix < nx-1; ++ix) {
        for(int iy = 1; iy < ny-1; ++iy) {
            // check that this cell is NOT a boundary condition or a border
            //if ( (ix == nx/2) && (ny/3 <= iy) && (iy <= 2*ny/3) ) continue;
            // update the cell
            data[ix*ny + iy] = (data[(ix+1)*ny + iy] + data[(ix-1)*ny + iy] + data[ix*ny + iy+1] + data[ix*ny + iy-1])/4.0;
        }
    }

}

void print_screen(const data_t & data, int nx, int ny)
{
    for(int ix = 0; ix < nx; ++ix) {
        for(int iy = 0; iy < ny; ++iy) {
            std::cout << data[ix*ny + iy] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_screen(const data_t & data, int nx, int ny, int pid, int np)
{
    int tag = 0;
    if (0 == pid) {
        print_screen(data, nx, ny);
        std::vector<double> buffer(nx*ny);
        for (int src = 1; src < np; ++src) {
            MPI_Recv(&buffer[0], nx*ny, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print_screen(buffer, nx, ny);
        }
    } else {
        int dest = 0;
        MPI_Send(&data[0], nx*ny, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }
}

void start_gnuplot(void)
{
    std::cout << "set pm3d\n";
    std::cout << "set contour base\n";
    std::cout << "set term gif animate\n";
    std::cout << "set output 'anim.gif'\n";
}

void print_gnuplot(const data_t & data, int nx, int ny)
{
    std::cout << "splot '-' w l lt 3 \n";
    for(int ix = 0; ix < nx; ++ix) {
        double x = XMIN + ix*DELTA;
        for(int iy = 0; iy < ny; ++iy) {
            double y = YMIN + iy*DELTA;
            std::cout << x << "  " << y << "  " << data[ix*ny + iy] << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "e\n";
}
