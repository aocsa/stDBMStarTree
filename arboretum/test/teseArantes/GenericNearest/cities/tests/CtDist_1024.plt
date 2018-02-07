set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	127.558000
0.002000	150.798000
0.005000	203.172000
0.010000	273.950000
0.020000	386.306000
0.050000	661.282000
0.100000	1064.496000
end
# SlimTree-NearestIntersection
0.001000	5800.510000
0.002000	5823.694000
0.005000	5875.044000
0.010000	5940.150000
0.020000	6035.814000
0.050000	6248.728000
0.100000	6528.564000
end
# SeqScan-Nearest
0.001000	5257.000000
0.002000	5257.000000
0.005000	5257.000000
0.010000	5257.000000
0.020000	5257.000000
0.050000	5257.000000
0.100000	5257.000000
end
# SeqScan-NearestIntersection
0.001000	10514.000000
0.002000	10514.000000
0.005000	10514.000000
0.010000	10514.000000
0.020000	10514.000000
0.050000	10514.000000
0.100000	10514.000000
end

pause -1