set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
set xrange [0.001:0.1]
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	4.706000
0.002000	4.908000
0.005000	5.422000
0.010000	6.138000
0.020000	7.430000
0.050000	10.106000
0.100000	13.198000
end
# SlimTree-RangeIntersection
0.001000	63.702000
0.002000	63.902000
0.005000	64.414000
0.010000	65.126000
0.020000	66.380000
0.050000	68.848000
0.100000	71.210000
end
# SeqScan-Nearest
0.001000	29.000000
0.002000	29.000000
0.005000	29.000000
0.010000	29.000000
0.020000	29.000000
0.050000	29.000000
0.100000	29.000000
end
# SeqScan-IntersectionNearest
0.001000	58.000000
0.002000	58.000000
0.005000	58.000000
0.010000	58.000000
0.020000	58.000000
0.050000	58.000000
0.100000	58.000000
end

pause -1