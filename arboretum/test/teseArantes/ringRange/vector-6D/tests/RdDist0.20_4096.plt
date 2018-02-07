set title "Conjunto de Dados: Cidades  page=4096, ratio (outer/inner) =0.20"
set logscale xy
set xlabel "% raio"
set ylabel "Nro. Médio de Cálculo de Distância"
plot '-' title '(A) Slim-Tree: RingRange' with linespoints lt 1 lw 2 pt 1, '-' title '(B) Slim-Tree: Basic Ranges' with linespoints lt 6 lw 2 pt 3, '-' title '(C) Slim-Tree: Single Range' with linespoints lt 3 lw 2 pt 4, '-' title '(D) SeqScan: RingRange' with linespoints lt 2 lw 2 pt 5, '-' title '(E) SeqScan: Basic Ranges' with linespoints lt 4 lw 2 pt 6, '-' title '(F) SeqScan: Single Range' with linespoints lt 5 lw 2 pt 2####################

# SlimTree-RingRange
0.001000	284.554000
0.002000	309.860000
0.005000	386.598000
0.010000	517.470000
0.020000	802.882000
0.050000	2055.540000
0.100000	6254.742000
end
# SlimTree-RingRange Intersection
0.001000	549.134000
0.002000	579.460000
0.005000	671.190000
0.010000	827.378000
0.020000	1163.952000
0.050000	2576.312000
0.100000	7096.748000
end
# SlimTree-Range
0.001000	264.444000
0.002000	269.388000
0.005000	284.074000
0.010000	308.932000
0.020000	359.008000
0.050000	512.062000
0.100000	790.754000
end
# SeqScan-RingRange
0.001000	49750.000000
0.002000	49750.000000
0.005000	49750.000000
0.010000	49750.000000
0.020000	49750.000000
0.050000	49750.000000
0.100000	49750.000000
end
# SeqScan-RingRange Intersection
0.001000	99500.000000
0.002000	99500.000000
0.005000	99500.000000
0.010000	99500.000000
0.020000	99500.000000
0.050000	99500.000000
0.100000	99500.000000
end
# SeqScan-Range
0.001000	49750.000000
0.002000	49750.000000
0.005000	49750.000000
0.010000	49750.000000
0.020000	49750.000000
0.050000	49750.000000
0.100000	49750.000000
end

pause -1