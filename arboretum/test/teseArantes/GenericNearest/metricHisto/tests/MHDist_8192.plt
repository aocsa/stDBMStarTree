set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	494.962000
0.002000	582.484000
0.005000	749.634000
0.010000	898.418000
0.020000	1100.220000
0.050000	1465.032000
0.100000	1862.000000
end
# SlimTree-NearestIntersection
0.001000	4990.938000
0.002000	5078.392000
0.005000	5245.138000
0.010000	5392.628000
0.020000	5591.248000
0.050000	5942.752000
0.100000	6309.420000
end
# SeqScan-Nearest
0.001000	4247.000000
0.002000	4247.000000
0.005000	4247.000000
0.010000	4247.000000
0.020000	4247.000000
0.050000	4247.000000
0.100000	4247.000000
end
# SeqScan-NearestIntersection
0.001000	8494.000000
0.002000	8494.000000
0.005000	8494.000000
0.010000	8494.000000
0.020000	8494.000000
0.050000	8494.000000
0.100000	8494.000000
end

pause -1