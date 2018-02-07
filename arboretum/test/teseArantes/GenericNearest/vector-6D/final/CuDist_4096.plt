set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	81.258000
0.002000	90.894000
0.005000	113.548000
0.010000	139.754000
0.020000	182.096000
0.050000	277.052000
0.100000	393.748000
end
# SlimTree-NearestIntersection
0.001000	2200.246000
0.002000	2209.880000
0.005000	2232.510000
0.010000	2258.528000
0.020000	2299.990000
0.050000	2378.142000
0.100000	2456.050000
end
# SeqScan-Nearest
0.001000	2061.000000
0.002000	2061.000000
0.005000	2061.000000
0.010000	2061.000000
0.020000	2061.000000
0.050000	2061.000000
0.100000	2061.000000
end
# SeqScan-NearestIntersection
0.001000	4122.000000
0.002000	4122.000000
0.005000	4122.000000
0.010000	4122.000000
0.020000	4122.000000
0.050000	4122.000000
0.100000	4122.000000
end

pause -1