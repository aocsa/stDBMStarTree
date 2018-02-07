set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Tempo Total (s)"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	0.578000
0.002000	0.781000
0.005000	1.407000
0.010000	2.766000
0.020000	7.203000
0.050000	37.109000
0.100000	141.391000
end
# SlimTree-RangeIntersection
0.001000	4125.500000
0.002000	4304.234000
0.005000	4835.093000
0.010000	5705.204000
0.020000	7439.110000
0.050000	12506.547000
0.100000	20442.829000
end
# SeqScan-Nearest
0.001000	10.109000
0.002000	10.250000
0.005000	11.437000
0.010000	14.812000
0.020000	27.594000
0.050000	113.844000
0.100000	369.015000
end
# SeqScan-NearestIntersection
0.001000	17468.438000
0.002000	17684.407000
0.005000	18332.578000
0.010000	19401.343000
0.020000	21520.953000
0.050000	27724.218000
0.100000	37462.687000
end

pause -1