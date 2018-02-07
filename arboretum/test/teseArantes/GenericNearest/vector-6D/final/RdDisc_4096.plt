set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	79.448000
0.002000	93.140000
0.005000	119.974000
0.010000	150.638000
0.020000	195.346000
0.050000	289.480000
0.100000	401.782000
end
# SlimTree-RangeIntersection
0.001000	1338.438000
0.002000	1352.116000
0.005000	1378.888000
0.010000	1409.386000
0.020000	1453.486000
0.050000	1544.388000
0.100000	1647.272000
end
# SeqScan-Nearest
0.001000	682.000000
0.002000	682.000000
0.005000	682.000000
0.010000	682.000000
0.020000	682.000000
0.050000	682.000000
0.100000	682.000000
end
# SeqScan-IntersectionNearest
0.001000	1364.000000
0.002000	1364.000000
0.005000	1364.000000
0.010000	1364.000000
0.020000	1364.000000
0.050000	1364.000000
0.100000	1364.000000
end

pause -1