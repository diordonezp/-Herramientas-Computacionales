#include<vector>
#include<cmath>

double entropy(std::vector<double> P)
{
    double E=0.0;
    
    /*es halla la entropía sumando los elementos P*ln(P). se descartan los
      P=0*/
    for(long unsigned int i=0;i<P.size();i++){
        if(P[i]!=0){
            E+=P[i]*std::log(P[i]);
        }
    }

    return -E;
}
