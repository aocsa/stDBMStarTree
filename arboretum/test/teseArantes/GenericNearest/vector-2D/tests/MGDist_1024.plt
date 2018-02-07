set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	274.180000
0.002000	356.680000
0.005000	559.500000
0.010000	839.000000
0.020000	1333.880000
end
# SlimTree-NearestIntersection
0.001000	28890.460000
0.002000	28969.240000
0.005000	29151.600000
0.010000	29383.340000
0.020000	29773.260000
end
# SeqScan-Nearest
0.001000	27032.000000
0.002000	27032.000000
0.005000	27032.000000
0.010000	27032.000000
0.020000	27032.000000
end
# SeqScan-NearestIntersection
0.001000	54064.000000
0.002000	54064.000000
0.005000	54064.000000
0.010000	54064.000000
0.020000	54064.000000
end

pause -1