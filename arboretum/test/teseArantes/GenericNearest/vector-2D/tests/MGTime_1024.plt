set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.015000
0.002000	0.016000
0.005000	0.016000
0.010000	0.062000
0.020000	0.172000
end
# SlimTree-RangeIntersection
0.001000	72.671000
0.002000	75.875000
0.005000	86.625000
0.010000	104.656000
0.020000	139.593000
end
# SeqScan-Nearest
0.001000	0.328000
0.002000	0.359000
0.005000	0.391000
0.010000	0.484000
0.020000	0.782000
end
# SeqScan-NearestIntersection
0.001000	448.625000
0.002000	447.704000
0.005000	488.703000
0.010000	499.766000
0.020000	548.969000
end

pause -1