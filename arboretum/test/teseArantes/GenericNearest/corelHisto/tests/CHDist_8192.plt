set title "Conjunto de Dados: Cidades  page=8192"
set logscale xy
set xlabel "k"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: GenericNearest' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Nearest' with linespoints lt 8 lw 2 pt 3, '-' title '(C) SeqScan: GenericNearest' with linespoints lt 3 lw 2 pt 2, '-' title '(D) SeqScan: Basic Nearest' with linespoints lt 6 lw 2 pt 6

####################
# SlimTree-Nearest
0.001000	12759.240000
0.002000	14850.980000
0.005000	18473.320000
0.010000	21972.620000
0.020000	26312.520000
end
# SlimTree-NearestIntersection
0.001000	84521.180000
0.002000	86610.740000
0.005000	90223.960000
0.010000	93702.460000
0.020000	97997.320000
end
# SeqScan-Nearest
0.001000	67790.000000
0.002000	67790.000000
0.005000	67790.000000
0.010000	67790.000000
0.020000	67790.000000
end
# SeqScan-NearestIntersection
0.001000	135580.000000
0.002000	135580.000000
0.005000	135580.000000
0.010000	135580.000000
0.020000	135580.000000
end

pause -1