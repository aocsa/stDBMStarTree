set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.031000
0.002000	0.032000
0.005000	0.047000
0.010000	0.047000
0.020000	0.063000
0.050000	0.140000
0.100000	0.281000
end
# SlimTree-RangeIntersection
0.001000	3.063000
0.002000	3.094000
0.005000	3.250000
0.010000	3.500000
0.020000	4.031000
0.050000	5.484000
0.100000	7.766000
end
# SeqScan-Nearest
0.001000	0.359000
0.002000	0.375000
0.005000	0.390000
0.010000	0.406000
0.020000	0.469000
0.050000	0.610000
0.100000	0.937000
end
# SeqScan-NearestIntersection
0.001000	8.203000
0.002000	8.218000
0.005000	8.422000
0.010000	8.657000
0.020000	9.297000
0.050000	11.031000
0.100000	13.891000
end

pause -1