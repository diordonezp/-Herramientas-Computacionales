#include<iostream>
#include<cstdlib>
//atoi para convertir char a int

int main(int argc, char *argv[])
{
  std::cout.precision(15);//notación decimal de 15 cifras
  std::cout.setf(std::ios::scientific);
  //argc para contar argumentos del comando
  //argv para listar cada argumento
  double under=1.0;
  double over=1.0;
  int N=std::atoi(argv[1]);

  std::cout<<"count: "<<0<<" under= "<<under<<" over= "<<over<<"\n";
  for(int i=0;i<N;i++){
    under/=2.0;//mejor ser explicito acerca del tipo de datos que trabajamos 
    over*=2.0;
    std::cout<<"count: "<<i+1<<" under= "<<under<<" over= "<<over<<"\n";
  }
  
  return 0;
}
