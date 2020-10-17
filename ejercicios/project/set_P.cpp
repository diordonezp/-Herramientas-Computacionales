#include<vector>

void set_P(std::vector<double> r,std::vector<double> &P,double l,int m,double dm)
{
    int N=r.size()/2;
    
    /*cada elemento de P cuenta la probabilidad (partículas en i/N)
      hay en cada casilla*/
    for(int k=0;k<r.size();k+=2){
        int ii=0;
        int jj=0;
        for(int i=0;i<m;i++){
            if(r[k]>=(-l+i*dm) && r[k]<(-l+i*dm+dm)){
                ii=i; 
            }
        }
        for(int i=0;i<m;i++){
            if(r[k+1]>=(-l+i*dm) && r[k+1]<(-l+i*dm+dm)){
                jj=i;
            }
        }
        P[jj*m+ii]+=1.0/N;
    }
}
