#include<iostream>

bool prime(int n);

int main(void)
{
  int n=5;
  
  std::cout<<prime(n)<<"\n";

  return 0;
}

bool prime(int n)
{
  bool res=true;

  if(n==1 || n==0){
    res=false;
  }

  for(int i=2;i<n;i++){
    if(n%i==0){
      res=false;
    }
  }

  return res;
}
