set title "Conjunto de Dados: Cidades  page=1024"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000 19.982000
0.002000 21.554000
0.005000 25.556000
0.010000 31.050000
0.020000 39.600000
0.050000 61.266000
0.100000 91.664000
end
# SlimTree-RangeIntersection
0.001000 436.974000
0.002000 438.538000
0.005000 442.480000
0.010000 447.784000
0.020000 455.540000
0.050000 473.594000
0.100000 496.236000
end
# SeqScan-Nearest
0.001000 183.000000
0.002000 183.000000
0.005000 183.000000
0.010000 183.000000
0.020000 183.000000
0.050000 183.000000
0.100000 183.000000
end
# SeqScan-IntersectionNearest
0.001000 366.000000
0.002000 366.000000
0.005000 366.000000
0.010000 366.000000
0.020000 366.000000
0.050000 366.000000
0.100000 366.000000
end

pause -1