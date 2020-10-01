plot "datos.txt" u 1:2 w l
set term pdf
set output "1.pdf"
replot
