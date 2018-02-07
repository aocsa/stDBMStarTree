set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	31.606000
0.002000	36.914000
0.005000	49.148000
0.010000	66.204000
0.020000	94.634000
0.050000	164.796000
0.100000	270.332000
end
# SlimTree-RangeIntersection
0.001000	1617.554000
0.002000	1622.760000
0.005000	1634.250000
0.010000	1649.370000
0.020000	1672.882000
0.050000	1723.416000
0.100000	1791.070000
end
# SeqScan-Nearest
0.001000	644.000000
0.002000	644.000000
0.005000	644.000000
0.010000	644.000000
0.020000	644.000000
0.050000	644.000000
0.100000	644.000000
end
# SeqScan-IntersectionNearest
0.001000	1288.000000
0.002000	1288.000000
0.005000	1288.000000
0.010000	1288.000000
0.020000	1288.000000
0.050000	1288.000000
0.100000	1288.000000
end

pause -1