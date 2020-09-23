#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

int main()
{
    std::cout << EIGEN_MAJOR_VERSION << std::endl;
    std::cout << EIGEN_MINOR_VERSION << std::endl;
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
}
