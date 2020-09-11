#include<iostream>

bool prime(int n);
int b_primes(int n);

int main(void)
{
    int N=1000;
    
    for(int i=0;i<=N;i++){
        std::cout<<i<<"\t"<<b_primes(i)<<"\n";
    }

    return 0;
}

bool prime(int n)
{
    bool res=true;

    if(n==0 || n==1){
        res=false;
    }

    for(int i=2;i<n;i++){
        if(n%i==0){
            res=false;
        }
    }
    return res;
}

int b_primes(int n)
{
    int sum=0;
    
    for(int i=0;i<=n;i++){
        if(prime(i)==1){
            sum+=1;
        }
    }
    return sum;
}
