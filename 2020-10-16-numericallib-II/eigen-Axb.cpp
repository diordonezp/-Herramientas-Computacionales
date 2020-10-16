#include <iostream>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
#include <chrono>

double solvesystem(int n);

int main(int argc, char **argv)
{
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    int N = std::atoi(argv[1]); 
    int REPS = std::atoi(argv[2]);

    double t = 0;
    for (int irep = 0; irep < REPS; ++irep) {
        t += solvesystem(N);
    }
    std::cout << t/REPS << std::endl;

    return 0;
}


double solvesystem(int n)
{
   Eigen::MatrixXd A(n, n);
   Eigen::VectorXd b(n);
   A = Eigen::MatrixXd::Random(n, n);
   b = Eigen::VectorXd::Random(n);
   //std::cout << "Here is the matrix A:\n" << A << std::endl;
   //std::cout << "Here is the vector b:\n" << b << std::endl;
   Eigen::VectorXd x(n) ;

   auto start = std::chrono::steady_clock::now();
   x = A.colPivHouseholderQr().solve(b);
   //x = A.partialPivLu().solve(b);
   auto end = std::chrono::steady_clock::now();
   double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()*1.0e-9;
   //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()*1.0e-9 << std::endl;
   //std::cout << "The solution is:\n" << x << std::endl;
   //std::cout << "Error: " << (A*x - b).norm() << std::endl;
   return time;
}
