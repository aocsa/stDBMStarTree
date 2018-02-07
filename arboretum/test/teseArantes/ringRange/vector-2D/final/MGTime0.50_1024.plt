set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	0.047000
0.002000	0.047000
0.005000	0.047000
0.010000	0.063000
0.020000	0.078000
0.050000	0.218000
0.100000	1.016000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.078000
0.005000	0.078000
0.010000	0.110000
0.020000	0.140000
0.050000	0.406000
0.100000	2.234000
end
# SlimTree-Range
0.001000	0.031000
0.002000	0.046000
0.005000	0.046000
0.010000	0.063000
0.020000	0.094000
0.050000	0.250000
0.100000	1.406000
end
# SeqScan-RingRange
0.001000	3.094000
0.002000	3.109000
0.005000	3.109000
0.010000	3.125000
0.020000	3.141000
0.050000	3.219000
0.100000	3.859000
end
# SeqScan-RingRange Intersection
0.001000	6.172000
0.002000	6.188000
0.005000	6.187000
0.010000	6.203000
0.020000	6.235000
0.050000	6.469000
0.100000	8.235000
end
# SeqScan-Range
0.001000	3.219000
0.002000	3.204000
0.005000	3.219000
0.010000	3.218000
0.020000	3.250000
0.050000	3.391000
0.100000	4.484000
end

pause -1