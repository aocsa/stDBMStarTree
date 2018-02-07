set title "Conjunto de Dados: Cidades  page=4096"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Acesso a Disco"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	4.620000
0.002000	4.760000
0.005000	5.140000
0.010000	5.580000
0.020000	6.780000
0.050000	9.920000
0.100000	12.760000
end
# SlimTree-RangeIntersection
0.001000	63.620000
0.002000	63.760000
0.005000	64.140000
0.010000	64.580000
0.020000	65.760000
0.050000	68.740000
0.100000	70.700000
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