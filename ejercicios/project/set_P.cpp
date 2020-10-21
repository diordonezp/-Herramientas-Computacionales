#include<vector>

void set_P(std::vector<double> r,std::vector<double> &P,double l,int m,double dm)
{
    int N=r.size()/2;
    
    /*cada elemento de P cuenta la probabilidad (partículas en i/N)
      hay en cada casilla*/
    for(long unsigned int k=0;k<r.size();k+=2){
        int ii=1;
        int jj=1;
        for(int i=0;i<m;i++){
            if(r[k]<=(-l+i*dm+dm)){
                ii=i;
                break;
            }
        }
        for(int i=0;i<m;i++){
            if(r[k+1]<=(-l+i*dm+dm)){
                jj=i;
                break;
            }
        }
        P[jj*m+ii]+=1.0;
    }
    for(long unsigned int i=0;i<P.size();i++){
        P[i]=P[i]/N;
    }
}
