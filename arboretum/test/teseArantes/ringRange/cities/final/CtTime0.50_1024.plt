set title "Conjunto de Dados: Cidades  page=1024, ratio (outer/inner) =0.50"
set logscale xy
set xlabel "% raio"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################
# SlimTree-RingRange
0.001000	0.031000
0.002000	0.047000
0.005000	0.063000
0.010000	0.078000
0.020000	0.125000
0.050000	0.500000
0.100000	2.140000
end
# SlimTree-RingRange Intersection
0.001000	0.078000
0.002000	0.094000
0.005000	0.093000
0.010000	0.125000
0.020000	0.235000
0.050000	1.078000
0.100000	5.891000
end
# SlimTree-Range
0.001000	0.046000
0.002000	0.031000
0.005000	0.047000
0.010000	0.062000
0.020000	0.141000
0.050000	0.704000
0.100000	3.719000
end
# SeqScan-RingRange
0.001000	0.985000
0.002000	0.984000
0.005000	0.984000
0.010000	1.016000
0.020000	1.062000
0.050000	1.391000
0.100000	2.797000
end
# SeqScan-RingRange Intersection
0.001000	1.969000
0.002000	1.969000
0.005000	1.985000
0.010000	2.015000
0.020000	2.109000
0.050000	2.953000
0.100000	7.813000
end
# SeqScan-Range
0.001000	0.985000
0.002000	1.000000
0.005000	1.000000
0.010000	1.016000
0.020000	1.093000
0.050000	1.656000
0.100000	4.593000
end

pause -1