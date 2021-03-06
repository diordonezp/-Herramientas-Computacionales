#include<iostream>
#include<cmath>
#include<chrono>

double fun(double x);
double integral(double a, double b,int h,int n);

int main(int argc,char **argv)
{
    std::cout.precision(15);std::cout.setf(std::ios::scientific);
    int num_threads=std::atoi(argv[1]);

    auto start=std::chrono::steady_clock::now();
    double I=integral(0,10,100000000,num_threads);
    auto end=std::chrono::steady_clock::now();

    double t=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()/1000.0;

    //con esta linea obtienes el valor de la integral para el número de hilos
	//std::cout<<num_threads<<" "<<I<<"\n";

    //con esta linea obtienes la eficiencia y el rendimiento de la paralelización
    std::cout<<num_threads<<" "<</t<<"\n";
	
	return 0;
}

double fun(double x)
{
	return std::pow(x,2);
}

double integral(double a,double b,int h,int n)
{
	double sum=0;
	double dx=(b-a)/h;

#pragma omp parallel for num_threads (n) reduction(+:sum)
	for(int i=1; i<h+1; i++){
		sum+=fun(a+i*dx);
	}
	return sum*dx;
}
