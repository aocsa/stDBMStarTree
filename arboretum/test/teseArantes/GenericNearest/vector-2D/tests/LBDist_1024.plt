set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	324.500000
0.002000	427.520000
0.005000	670.520000
0.010000	1015.940000
0.020000	1607.440000
end
# SlimTree-NearestIntersection
0.001000	38459.640000
0.002000	38555.260000
0.005000	38768.440000
0.010000	39048.240000
0.020000	39501.800000
end
# SeqScan-Nearest
0.001000	36048.000000
0.002000	36048.000000
0.005000	36048.000000
0.010000	36048.000000
0.020000	36048.000000
end
# SeqScan-NearestIntersection
0.001000	72096.000000
0.002000	72096.000000
0.005000	72096.000000
0.010000	72096.000000
0.020000	72096.000000
end

pause -1