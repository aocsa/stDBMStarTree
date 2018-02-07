set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	79.600000
0.002000	89.980000
0.005000	111.000000
0.010000	131.520000
0.020000	172.780000
0.050000	266.580000
0.100000	391.080000
end
# SlimTree-NearestIntersection
0.001000	2198.600000
0.002000	2208.980000
0.005000	2230.000000
0.010000	2250.480000
0.020000	2291.380000
0.050000	2363.920000
0.100000	2443.000000
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