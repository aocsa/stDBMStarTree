set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.047000
0.002000	0.078000
0.005000	0.140000
0.010000	0.266000
0.020000	0.719000
end
# SlimTree-RangeIntersection
0.001000	405.812000
0.002000	440.016000
0.005000	478.921000
0.010000	578.343000
0.020000	746.656000
end
# SeqScan-Nearest
0.001000	1.031000
0.002000	1.047000
0.005000	1.188000
0.010000	1.484000
0.020000	2.672000
end
# SeqScan-NearestIntersection
0.001000	2130.000000
0.002000	2299.297000
0.005000	2221.704000
0.010000	2474.141000
0.020000	2549.766000
end

pause -1