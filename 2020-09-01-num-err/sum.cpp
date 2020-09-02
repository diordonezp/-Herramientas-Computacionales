#include<iostream>
#include<cmath>

double sum(double x, int N);

int main(int argc, char*argv[])
{
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);

  float x=std::atof(argv[1]);
  int N=std::atoi(argv[2]);

  std::cout<<sum(x,N)<<"\n";
  
  return 0;
}

double sum(double x, int N)
{
  double tot=1.0;
  double term=1.0;

  for(int i=1;i<=N;i++){
    term*=(-x)/(i);
    tot+=term;
  }

  return tot;
}
