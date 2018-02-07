set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.078000
0.002000	0.063000
0.005000	0.110000
0.010000	0.156000
0.020000	0.250000
0.050000	0.625000
0.100000	1.547000
end
# SlimTree-RangeIntersection
0.001000	24.672000
0.002000	24.891000
0.005000	25.532000
0.010000	26.875000
0.020000	28.907000
0.050000	34.594000
0.100000	42.437000
end
# SeqScan-Nearest
0.001000	1.000000
0.002000	0.984000
0.005000	1.031000
0.010000	1.188000
0.020000	1.390000
0.050000	2.250000
0.100000	4.266000
end
# SeqScan-NearestIntersection
0.001000	59.312000
0.002000	59.640000
0.005000	60.593000
0.010000	62.000000
0.020000	65.156000
0.050000	71.797000
0.100000	85.547000
end

pause -1