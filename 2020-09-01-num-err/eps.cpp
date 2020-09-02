#include<iostream>
#include<cstdlib>
//atoi para convertir char a int

int main(int argc, char *argv[])
{
  std::cout.precision(7);//notación decimal de 15 cifras
  std::cout.setf(std::ios::scientific);
  //argc para contar argumentos del comando
  //argv para listar cada argumento
  float eps=1.0;
  float one=1.0;
  int N=std::atoi(argv[1]);

  std::cout<<"count: "<<0<<" lc= "<<one<<" eps= "<<eps<<"\n";
  for(int i=0;i<N;i++){
    eps/=2.0; 
    one=1.0+eps;
    std::cout<<"count: "<<i+1<<" lc= "<<one<<" eps= "<<eps<<"\n";
  }
  
  return 0;
}
