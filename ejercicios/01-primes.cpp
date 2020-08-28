#include<iostream>

bool prime(int n);
void f(int n, int m);

int main(void)
{  
  f(500,12100);

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

void f(int n,int m)
{
  int sum=0;
  int count=0;
  
  for(int i=n;i<=m;i++){
    if(prime(i)==1){
      sum+=i;
      count+=1;
    }
  }
  std::cout<<"hay "<<count<<" primos que suman: "<<sum<<"\n";
}
