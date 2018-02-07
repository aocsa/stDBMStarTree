set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	1586.260000
0.002000	1992.200000
0.005000	2803.280000
0.010000	3749.800000
0.020000	5178.080000
end
# SlimTree-NearestIntersection
0.001000	52594.100000
0.002000	52999.020000
0.005000	53803.180000
0.010000	54732.120000
0.020000	56100.700000
end
# SeqScan-Nearest
0.001000	49750.000000
0.002000	49750.000000
0.005000	49750.000000
0.010000	49750.000000
0.020000	49750.000000
end
# SeqScan-NearestIntersection
0.001000	99500.000000
0.002000	99500.000000
0.005000	99500.000000
0.010000	99500.000000
0.020000	99500.000000
end

pause -1