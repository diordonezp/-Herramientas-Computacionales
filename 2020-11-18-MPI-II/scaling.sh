#!/bin/bash 

for NS in 1000000 10000000 100000000; do
    echo "Starting strong scaling with system size: $NS"
    for NTH in 1 2 3 4 5 6 7 8 16 32; do
	echo -n "$NTH  ";
	./a.out $NS $NTH | head -n 1;
    done > scaling-$NS.txt
    
    echo "Computing parallel metrics from file scaling-$NS.txt ..."
    awk 'BEGIN {TS=1.0;} { if(NR==1) TS=$2;  print $1, $2, TS/$2, TS/$2/$1}' scaling-$NS.txt > metrics-$NS.txt
    echo "Metrics saved to: metrics-$NS.txt"
done
echo "Done"
