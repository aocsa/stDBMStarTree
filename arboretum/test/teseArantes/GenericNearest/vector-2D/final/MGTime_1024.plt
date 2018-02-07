set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.375000
0.002000	0.140000
0.005000	0.328000
0.010000	0.609000
0.020000	1.625000
0.050000	8.468000
0.100000	33.062000
end
# SlimTree-RangeIntersection
0.001000	592.047000
0.002000	624.203000
0.005000	727.437000
0.010000	893.828000
0.020000	1227.515000
0.050000	2211.906000
0.100000	3760.407000
end
# SeqScan-Nearest
0.001000	3.406000
0.002000	3.422000
0.005000	3.860000
0.010000	4.766000
0.020000	7.719000
0.050000	26.938000
0.100000	92.953000
end
# SeqScan-NearestIntersection
0.001000	5077.672000
0.002000	5124.641000
0.005000	5270.282000
0.010000	5527.922000
0.020000	5990.891000
0.050000	7374.328000
0.100000	9562.093000
end

pause -1