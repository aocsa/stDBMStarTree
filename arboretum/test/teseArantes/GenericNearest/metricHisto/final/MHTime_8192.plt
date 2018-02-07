set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	1.546000
0.002000	1.828000
0.005000	2.312000
0.010000	2.781000
0.020000	3.437000
0.050000	4.828000
0.100000	6.813000
end
# SlimTree-RangeIntersection
0.001000	35.187000
0.002000	35.656000
0.005000	36.875000
0.010000	38.391000
0.020000	41.078000
0.050000	48.343000
0.100000	58.297000
end
# SeqScan-Nearest
0.001000	11.360000
0.002000	11.375000
0.005000	11.469000
0.010000	11.563000
0.020000	11.844000
0.050000	12.719000
0.100000	14.531000
end
# SeqScan-NearestIntersection
0.001000	67.157000
0.002000	67.422000
0.005000	68.312000
0.010000	69.687000
0.020000	72.532000
0.050000	80.219000
0.100000	91.563000
end

pause -1