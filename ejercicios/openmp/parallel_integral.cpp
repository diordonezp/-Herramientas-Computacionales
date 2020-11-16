#include<iostream>
#include<cmath>

double fun(double x);
double integral(double a, double b, double h);

int main(void)
{
	std::cout << integral(0,10,10000000)
	<<std::endl;
	
	return 0;
}

double fun(double x)
{
	return std::pow(x,2);
}

double integral(double a, double b, double h)
{
	double sum=0;
	double dx=(b-a)/h;

	for(int i=1; i<=h; i++){
		sum+=fun(a+i*dx);
	}
	return sum*dx;
}
