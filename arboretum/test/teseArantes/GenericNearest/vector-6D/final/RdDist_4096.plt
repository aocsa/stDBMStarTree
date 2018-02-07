set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	1659.850000
0.002000	2088.008000
0.005000	2943.146000
0.010000	3953.274000
0.020000	5487.414000
0.050000	8878.848000
0.100000	13165.956000
end
# SlimTree-NearestIntersection
0.001000	52667.582000
0.002000	53094.708000
0.005000	53943.344000
0.010000	54935.026000
0.020000	56414.414000
0.050000	59550.136000
0.100000	63243.100000
end
# SeqScan-Nearest
0.001000	49750.000000
0.002000	49750.000000
0.005000	49750.000000
0.010000	49750.000000
0.020000	49750.000000
0.050000	49750.000000
0.100000	49750.000000
end
# SeqScan-NearestIntersection
0.001000	99500.000000
0.002000	99500.000000
0.005000	99500.000000
0.010000	99500.000000
0.020000	99500.000000
0.050000	99500.000000
0.100000	99500.000000
end

pause -1