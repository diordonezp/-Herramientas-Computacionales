for N in 1 2 10 100 200 500 ; do
    echo -n "$N  "
    ./a.out $N 1
done > datos.txt

cat<<EOF > script.gp
set log xy
f(x) = A*x**B
A=1.0e-4; B=3;
fit f(x) 'datos.txt' via A, B
set xlabel 'N'
set ylabel 'CPU time (s)'
set term pdf 
set out "fig.pdf"
plot 'datos.txt' w lp lw 4 t 'datos', f(x) lw 5 t 'fit'
EOF

gnuplot script.gp
