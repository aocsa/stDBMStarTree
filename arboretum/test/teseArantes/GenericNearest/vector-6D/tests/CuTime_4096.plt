set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.000000
0.002000	0.016000
0.005000	0.000000
0.010000	0.000000
0.020000	0.016000
0.050000	0.015000
0.100000	0.031000
end
# SlimTree-RangeIntersection
0.001000	0.281000
0.002000	0.282000
0.005000	0.312000
0.010000	0.329000
0.020000	0.375000
0.050000	0.531000
0.100000	0.766000
end
# SeqScan-Nearest
0.001000	0.031000
0.002000	0.031000
0.005000	0.047000
0.010000	0.047000
0.020000	0.047000
0.050000	0.063000
0.100000	0.094000
end
# SeqScan-NearestIntersection
0.001000	0.859000
0.002000	0.859000
0.005000	0.875000
0.010000	0.906000
0.020000	0.969000
0.050000	1.156000
0.100000	1.453000
end

pause -1