for N in 1 2 3 4 5 6 7 8; do
    ./a.out $N
done > time.txt

awk 'BEGIN{Ts=0}{if(NR==1)Ts=$2;print $0,Ts/$2,(Ts/$2)/$1}' time.txt>metrics.txt
